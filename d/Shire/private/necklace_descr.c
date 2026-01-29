/* Smith Necklace descriptions */

#include "/d/Shire/sys/defs.h"
#include <macros.h>

string necklace_type;

string describe_necklace()
{
    int lvl;
    lvl = TP->query_stat(SS_LAYMAN);
    switch (lvl)
    {
        case   0..5:   return "rough iron";         break;
        case   6..11:  return "dingy iron";         break;
        case  12..17:  return "flat coloured iron"; break;
        case  18..24:  return "dull iron";          break;
        case  25..32:  return "faded iron";         break;
        case  33..40:  return "faint iron";         break;
        case  41..49:  return "pale iron";          break;
        case  50..58:  return "glowing iron";       break;
        case  59..68:  return "bright iron";        break;
        case  69..79:  return "sparkling iron";     break;
        case  80..92:  return "shining steel";      break;
        case  93..105: return "vivid steel";        break;
        case 106..119: return "intense steel";      break;
        case 120..134: return "splendid steel";     break;
        case 135..150: return "lustrous steel";     break;
        case 151..167: return "radiant steel";      break;
        case 168..184: return "glorious steel";     break;
        case 185..199: return "dazzling steel";     break;
        default:       return "priceless mithril";  break;
    }
    return necklace_type;
}

