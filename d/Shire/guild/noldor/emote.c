/*
 * The emote header file for the Noldor racial guild.
 * This file loads the references to the emotes.
 *-- Finwe, May 2001
 */

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "noldor.h"
#include "/d/Shire/guild/noldor/emotes/do_help.c"

inherit "/cmd/std/command_driver";

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());
    
	return ([
      "help"            : "do_help",
      "nolist"          : "list_active_noldor",
      "noldorlist"      : "list_active_noldor",
      "noacknowledge"   : "nacknowledge",
      "noac"            : "nacknowledge",
      "noattack"        : "nattack",
      "noat"            : "nattack",
      "nocall"          : "ncall",
      "noca"            : "ncall",
      "noclean"         : "nclean",
      "nocl"            : "nclean",
      "nodismiss"       : "ndismiss",
      "nodi"            : "ndismiss",
      "nofarewell"      : "nfarewell",
      "nofa"            : "nfarewell",
	  "noignore"        : "nignore",
	  "noig"            : "nignore",
      "nohymn"          : "nhymn",
      "nohy"            : "nhymn",
      "nopolish"        : "npolish",
      "nopo"            : "npolish",
      "noremind"        : "nremind",
      "nore"            : "nremind", 
      "nooath"          : "noath",
      "nooa"            : "noath", 
      "nopause"         : "npause",
      "nopa"            : "npause",
      "notear"          : "ntear",
      "note"            : "ntear",
      "nowelcome"       : "nwelcome",
      "nowe"            : "nwelcome",
      "nolist"          : "list_active_noldor",
      "noli"            : "list_active_noldor",
    ]);

}
