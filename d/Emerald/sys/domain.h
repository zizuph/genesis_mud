#ifndef EMERALD_DOMAIN_HEADER
#define EMERALD_DOMAIN_HEADER

#include <std.h>

#define DOMAIN_NAME "Emerald"

#define DOMAIN_NUMBER (SECURITY->query_domain_number(DOMAIN_NAME))

#define DOMAIN_WIZ(x) (interactive(x) && \
   SECURITY->query_wiz_dom(x->query_real_name()) == DOMAIN_NAME)

#endif
