inherit "/std/shadow";
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <language.h>

string
query_the_name(object who)
{
   if (who->query_wiz_level())
      return "the black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "the black cloaked figure";
}

string
query_nonmet_name(object who)
{
   if (who->query_wiz_level())
      return "black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "black cloaked figure";
}

string
query_The_name(object who)
{
   if (who->query_wiz_level())
      return "The black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "The black cloaked figure";
}

string
short(object who)
{
   if (who->query_wiz_level())
      return "black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "black cloaked figure";
}

string
query_art_name(object who)
{
   if (who->query_wiz_level())
      return "a black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "a black cloaked figure";
}

string
query_Art_name(object who)
{
   if (who->query_wiz_level())
      return "A black cloaked figure ("+shadow_who->query_name()+")";
   else
      return "A black cloaked figure";
}
