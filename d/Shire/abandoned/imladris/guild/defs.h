#include "../include/defs.h"

#ifndef _GUILD_DEFS_H
#define _GUILD_DEFS_H

#define ListFile(i)	(string)  LIST_FILES[i]
#define QLists(tp)	(int *)   tp->query_spell_list_ids()

#define DEBUG(str) \
   if (strlen(DEBUG_FILE)) log_file(DEBUG_FILE, str, 0);

#endif
