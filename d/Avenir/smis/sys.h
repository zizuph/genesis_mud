// file name:        /d/Avenir/smis/sys.h
// creator(s):       Denis, May'96
// purpose:          Some definitions relying upon the implementation of
//		     security mechanisms (It changes from time to time,
//		     doesn't it?) and domains structure.
/*
 * Revisions:
 *     Lucius, Jul 2017: Cleanups.
 */
#ifndef SMIS_SYS_H
#define SMIS_SYS_H

#include <files.h>
#include <std.h>

/* This macro gives the name of this_object() domain.
 */
#define OBJECT_DOMAIN			"Avenir"
#ifndef OBJECT_DOMAIN
# define OBJECT_DOMAIN			SECURITY->domain_object(this_object())
#endif

#ifndef SMIS_MANAGER
# define SMIS_MANAGER			("/d/"+ OBJECT_DOMAIN +"/smis/smis_mgr")
#endif

#define SMIS_MANAGER_DOM(dom)		("/d/"+ dom +"/smis/smis_mgr")

#define SMIS_WRITE_LOG(str) \
    write_file("/d/"+ OBJECT_DOMAIN +"/log/smis", ctime(time()) +" "+ str)

/* The macro that gives non-0 if fomain dom exists and 0 otherwise.
 */
#define SMIS_DOMAIN_EXISTS(dom)	\
    (SECURITY->query_domain_number(dom) > -1)

#define SMIS_WIZARD_DOMAIN_OB(wiz) \
    SECURITY->query_wiz_dom(wiz->query_real_name())

/* The macro that gives 1 for the ones who can access a restricted feature
 * and 0 for those who should not.
 */
#define SMIS_ACCESS_ALLOWED(obj) \
    (SECURITY->query_wiz_dom(obj->query_real_name()) == OBJECT_DOMAIN || \
	SECURITY->query_wiz_rank(obj->query_real_name()) >= WIZ_ARCH)

#define SMIS_CHECK_CALLER \
    if (previous_object() != this_object() && \
	!query_module_open() && \
	!SMIS_ACCESS_ALLOWED(this_interactive()) && \
	file_name(previous_object()) != SMIS_MANAGER) { return 0; }

#endif
