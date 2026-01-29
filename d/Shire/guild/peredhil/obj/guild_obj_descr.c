/* 
 * /d/Shire/guild/peredhil/obj/guild_obj_descr.c
 *
 * Peredhil guild object descriptions
 * Based on the Smiths necklace description
 * Finwe, February 2009
 */

#include "/d/Shire/sys/defs.h"
#include <macros.h>

string guild_obj_descr;

string describe_guild_obj()
{
    int lvl;

    lvl = TP->query_stat(6);
    
    switch (lvl)
    {
        case   0..9:    return "plain copper";      break;
        case  10..19:   return "dull copper";       break;
        case  20..29:   return "brushed copper";    break;
        case  30..39:   return "smooth copper";     break;
        case  40..49:   return "polished copper";   break;
        case  50..59:   return "plain brass";       break;
        case  60..69:   return "dull brass";        break;
        case  70..79:   return "brushed brass";     break;
        case  80..89:   return "smooth brass";      break;
        case  90..99:   return "polished brass";    break;
        case 100..109:  return "plain silver";      break;
        case 110..119:  return "dull silver";       break;
        case 120..129:  return "brushed silver";    break;
        case 130..139:  return "smooth silver";     break;
        case 140..149:  return "polished silver";   break;
        case 150..159:  return "plain golden";      break;
        case 160..169:  return "dull golden";       break;
        case 170..179:  return "brushed golden";    break;
        case 180..189:  return "smooth golden";     break;
        case 190..199:  return "polished golden";   break;
        default:        return "polished mithril";  break;
    }
    return guild_obj_descr;
}

