/* File:          /d/Khalakhor/common/herbs/shamrock.c
 * Creator:       Teth
 * Date:          January 16, 1998
 * Modifications: Teth, Jan 19, 1998 - added special effects. 
 * Added consistent singular and plural names - Tapakah, 04/2021
 * Purpose:       This herb will be found in gardens, and it gives 
 *                a lucky minor random effect.
 * Related Files: /std/resistance.c
 * Comments:      This herb is intended to be common, yet special.
 *                The random effect does not have to be saved in
 *                recovery because it is always random? or is this
 *                sloppy? Someone may have an ability to query an 
 *                herb's effect one day, and then recovery would change
 *                it.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"

void random_effect();

public void
create_herb()
{
  set_name("leaf");
  add_name("shamrock");
  set_adj("trifoil");
  add_adj("green");
  set_herb_name("shamrock");
  set_short("trifoil leaf");
  set_pshort("trifoil leaves");
  set_pname(({"leaves", "herbs", "shamrocks"}));
  set_ingest_verb("eat");
  set_unid_long("This trifoil leaf is emerald green in colour, " +
                "and has a slender stipe. It was probably picked from a " +
                "garden.\n");
  set_id_long("This trifoil leaf is from the perennial plant " +
              "commonly known as shamrock. Shamrock (Oxalis regnellii) " +
              "is an herb often found in mixed woods forests and " +
              "gardens. The leaf is emerald green in colour, with " +
              "three horseshoe-shaped leaflets radiating from the " +
              "central stipe. When flowering, shamrock blooms with " +
              "delicate white flowers. Once picked, the leaves are " +
              "quite susceptible to wilting. The shamrock is known for " +
              "luck.\n");
  set_herb_value(290);
  set_id_diff(12);
  set_find_diff(5);
  set_decay_time(350); /* 5 minutes, these plants wilt easily RL! */
  set_amount(1);

  random_effect();
}

public void
random_effect()
{
  int rndeffect;
  int rndstrength;

  rndeffect = random(11);
  rndstrength = random(4) + 1;

  switch(rndeffect)
    {
    case 0:
      set_effect(HERB_ENHANCING, "str", rndstrength);
      break;
    case 1:
      set_effect(HERB_ENHANCING, "dex", rndstrength);
      break;
    case 2:
      set_effect(HERB_ENHANCING, "con", rndstrength);
      break;
    case 3:
      set_effect(HERB_ENHANCING, "int", rndstrength);
      break;
    case 4:
      set_effect(HERB_ENHANCING, "wis", rndstrength);
      break;
    case 5:
      set_effect(HERB_ENHANCING, "dis", rndstrength);
      break;
    case 6:
      set_effect(HERB_ENHANCING, "acid", rndstrength);
      break;
    case 7:
      set_effect(HERB_ENHANCING, "cold", rndstrength);
      break;
    case 8:
      set_effect(HERB_ENHANCING, "electr", rndstrength);
      break;
    case 9:
      set_effect(HERB_ENHANCING, "fire", rndstrength);
      break;
    case 10:
      set_effect(HERB_ENHANCING, "magic", rndstrength);
      break;
    default:
      set_effect(HERB_ENHANCING, "poison", rndstrength);
      break;
    }    
}


public string
query_recover() 
{
  return MASTER+":"+query_herb_recover();
}

public void
init_recover(string arg) 
{ 
  init_herb_recover(arg); 
}


