/*******************************************************************\
| BASH_GLOVES.C                                                     |
+-------------------------------------------------------------------+
| A standard armour object that adds a shadow to its wearer to      |
| provide for an extra stun effect while fighting.                  |
\*******************************************************************/

/*
 * 01/11/01 Tijgen	Created sometime around this time
 * 01/11/26 Arandir	Cleaned up and removed superfluous code
 *
 */

#include "bash_gloves.h"

inherit "/std/armour";

#include <wa_types.h>

//-------------------------------------------------------------------

/*******************************************************************\
| Constructor and destructor functions.                             |
\*******************************************************************/

/*
 * Function name : create_armour
 * Description   : Creates the armour object
 *
 */

void create_armour ()
{
   set_name   ("gloves");
   set_short  ("pair of plated leather gloves");
   set_pshort ("pairs of plated leather gloves");
   set_adj    (({"plated", "leather"}));
   set_long   ("@@vbfc_long_desc@@");

   set_at     (A_HANDS);
   set_ac     (20);
   set_af     (this_object ());
}

/*
 * Function name : vbfc_long_desc
 * Description   : Returns the long description of the gloves
 *
 */

string vbfc_long_desc ()
{
  string sDesc;
  
  sDesc = "You see a pair of long leather gloves. Made for " +
          "combat, they reach to the elbows and are covered " +
          "with small plates made of silvery metal, arranged " +
          "in a pattern that resembles serpentine skin. The " +
          "plates end near the fingers so as not to limit " +
          "flexibility.";

  if (query_worn ())
  {
    sDesc += " As you move your hands, you feel as if they " +
             "were picking up more momentum than the weight " +
             "of the gloves would account for.";
  };
  
  sDesc += "\n";
  
  return (sDesc);
}

//-------------------------------------------------------------------

/*******************************************************************\
| Wear and remove functions.                                        |
\*******************************************************************/

/*
 * Function name : wear
 * Description   : Called when the gloves are worn
 *
 */

int wear ()
{
  object oShadow;
  
  // When wearing the gloves, we shadow the wearer to intercept
  // the hit callback. Note that a new instance of the shadow
  // object is created every time the gloves are worn, because
  // the only way to remove the shadow is to destroy it.

  seteuid (getuid());
  oShadow = clone_object (BG_SHADOW_FILE);
  oShadow->bg_attach_shadow (this_player ());

  return (0);
}

int remove ()
{
  object oWearer;
  oWearer = query_worn ();
  oWearer->bg_destroy_shadow ();
  
  return (0);
}

//-------------------------------------------------------------------
