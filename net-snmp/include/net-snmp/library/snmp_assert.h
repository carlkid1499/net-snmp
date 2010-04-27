#ifndef SNMP_ASSERT_H
#define SNMP_ASSERT_H

#ifdef NETSNMP_USE_ASSERT
#   include <assert.h>
#else
#   include <net-snmp/library/snmp_logging.h>
#endif


/*
 * MACROs don't need extern "C"
 */

/*
 * define __STRING for systems (*cough* sun *cough*) that don't have it
 */
#ifndef __STRING
#  if defined(__STDC__) || defined(_MSC_VER)
#    define __STRING(x) #x
#  else
#    define __STRING(x) "x"
#  endif /* __STDC__ */
#endif /* __STRING */

/*
 * always use assert if requested
 */
#ifdef NETSNMP_USE_ASSERT
/*   void netsnmp_assert( int );*/
#   define netsnmp_assert(x)  assert( x )
#   define netsnmp_assert_or_return(x, y)  assert( x )
#   define netsnmp_assert_or_msgreturn(x, y, z)  assert( x )
#else
/*
 *  if asserts weren't requested, just log, unless NETSNMP_NO_DEBUGGING specified
 */
#   ifndef NETSNMP_NO_DEBUGGING
#      ifdef  NETSNMP_FUNCTION
#          define NETSNMP_FUNC_FMT " %s()\n"
#          define NETSNMP_FUNC_PARAM NETSNMP_FUNCTION
#      else
#          define NETSNMP_FUNC_FMT "%c"
#          define NETSNMP_FUNC_PARAM '\n'
#      endif
#
#      define netsnmp_assert(x)  do { \
              if ( x ) \
                 ; \
              else \
                 snmp_log(LOG_ERR, \
                          "netsnmp_assert %s failed %s:%d" NETSNMP_FUNC_FMT, \
                          __STRING(x),__FILE__,__LINE__, \
                          NETSNMP_FUNC_PARAM); \
           }while(0)
#      define netsnmp_assert_or_return(x, y)  do {        \
              if ( x ) \
                 ; \
              else { \
                 snmp_log(LOG_ERR, \
                          "netsnmp_assert %s failed %s:%d" NETSNMP_FUNC_FMT, \
                          __STRING(x),__FILE__,__LINE__, \
                          NETSNMP_FUNC_PARAM); \
                 return y; \
              } \
           }while(0)
#      define netsnmp_assert_or_msgreturn(x, y, z)  do {       \
              if ( x ) \
                 ; \
              else { \
                 snmp_log(LOG_ERR, \
                          "netsnmp_assert %s failed %s:%d" NETSNMP_FUNC_FMT, \
                          __STRING(x),__FILE__,__LINE__, \
                          NETSNMP_FUNC_PARAM); \
                 snmp_log(LOG_ERR, y); \
                 return z; \
              } \
           }while(0)
#   else /* NO DEBUGGING */
#      define netsnmp_assert(x)
#      define netsnmp_assert_or_return(x, y)  do {        \
                 if ( x ) \
                    ; \
                 else { \
                    return y; \
                 } \
              }while(0)
#      define netsnmp_assert_or_msgreturn(x, y, z)  do {       \
                 if ( x ) \
                    ; \
                 else { \
                    return z; \
                 } \
              }while(0)
#   endif /* NO DEBUGGING */
#endif /* not NETSNMP_USE_ASSERT */


#endif /* SNMP_ASSERT_H */
