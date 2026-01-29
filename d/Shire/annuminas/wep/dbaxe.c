/*
 * /d/Shire/annuminas/wep/dbaxe.c
 * Double-bladed battleaxe
 * Forged ages ago by the thralls of Melkor, the axe has 
 * survived. It endows players with temporary str when they 
 * 'pledge soul'. It is also only wieldable by evil players.
 * -- Finwe, July 2002
 * 
 * 2020-12-21 - Cotillion
 * - Fixed accidental non-dulling
 * - Also removed the wild random on hit/pen 40 + ran(5) and, 
 *   35 + ran(10) as this made the weapon very unpredictable for
 *   players.
 */

inherit "/std/weapon";
inherit "/lib/keep";


#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
 
int pledged = 0;
int hit = 44;
int pen = 43;

//#define DBA_MAX_ALIGN   -160

void
create_weapon()
{
    set_name("axe");
    add_name("battleaxe");
    add_name("battle axe");
    set_adj("double-bladed");
    set_adj("battle");
    set_short("double-bladed battleaxe");
    set_long("This "+short()+" looks ancient and dark. It was probably " +
        "forged by fell servants of the Dark One and has survived all " +
        "these ages. The handle is made from an unknown, black metal with " +
        "two axe blades attached to the top making the axe expertly " +
        "balanced. The blades are made from steel and look sharp enough " +
        "to slash through the hardest material. There are dark engravings " +
        "on the blade.\n");
    add_item(({"blades", "blade"}),
        "The blades are in the shape of half circles, and attached to " +
        "the top of the handle. Their edges are sharped and look to be " +
        "able to slash through anything. Dark engravings are etched into " +
        "the blade and seem to glow with a fell power.\n");
    add_item("handle", 
        "The handle is made of some unknown black metal. Deep within " +
        "the handle, tormented images of souls flit about, who once " +
        "pledged their souls to the Dark One. \n");
    add_item(({"engravings", "dark engravings"}),
        "The engravings look evil and debased, probably spells or " +
        "enchantments to enhance the power of the battleaxe. Only the " +
        "strongest are able to decipher their meaning.\n");

    set_default_weapon(hit, pen, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 8000 + random(500));
    add_prop(OBJ_I_VOLUME, 1500 + random(200));
    add_prop(OBJ_I_VALUE, 2400 + random(151));
 
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "An evil batteaxe with strong powers emanating from it.\n",5,
        "The engravings burn with a fell power.\n", 15,
        "The blade seems to whisper, calling you to pledge your soul to it.\n",20,
        "A feeling of strength seems to enter your being.\n",40}));
    add_prop(OBJ_S_WIZINFO,"This "+short()+" endows players with " +
        "temporary strength when they pledge their soul to it and takes " +
        "10% of their mana.\n");

    set_wf (TO);
}
 
void
init()
{
    ::init();
    add_action("do_pledge","pledge");
    add_action("do_decipher","decipher");
}


public mixed wield (object wep)
{
    /*
     * Checks alignment. if evil, player cant wield blade
     */
/*
    if (TP->query_alignment() > DBA_MAX_ALIGN)
    {
      tell_room(ENV(TP),QCTNAME(TP)+" screams in sudden horror and drops the "+
                short()+". The battleaxe clatters as it hits the ground!\n", ({TP}));
      write ("You scream in utter horror as evil images suddenly swirl " +
             "in your mind. You drop the "+short()+"!\n");
      move(ENV(TP), 1);
      return ("");          
    };
*/    
    /*
     * Check to see if player is skilled enough
     */

    if(TP->query_skill(SS_WEP_AXE) < 50)
    {
        return ("You lack the skill to wield this terrible battleaxe.\n");
    };
    
    // All OK, wield it ...

    write("You raise the "+short()+" above your head and yell a battlecry!\n");
    say(QCTNAME(TP) + " wields the "+short() + " above "+ HIS_HER(TP)+
        " head and yells a battlecry!\n");

    return (1);
}

public mixed unwield (object wep)
{
  return (0);
}

void renew_pledge(object oMe)
{
    pledged = 0;
    if(!objectp(oMe)) return; //sanity check, Milan
    oMe->catch_msg ("The power of the "+short()+" leaves your body and your " +
        "countenance returns to normal.\n");
    tell_room (environment (oMe), QCTNAME(oMe)+" begins to relax as " +HIS_HER(oMe)+", countenance " +
        "returns to normal.\n", oMe);
}


int do_pledge(string str)
{
    int iMana, iPenalty;
  
    if (!str) return (0);
    notify_fail ("Pledge what?\n");

    if (str == "soul" || str == "my soul")
    {
      if(!pledged && TO->query_wielded())
      {
          iMana = TP->query_mana ();
          iPenalty = 10 + random(iMana/10);
          if (iMana < iPenalty)
          {
              write ("Your lips move but you cannot seem to utter " +
                     "the pledge with what remains of your " +
                     "parched soul.\n");
              say (QCTNAME(TP) + " moves " + HIS_HER(TP) + " lips " +
                   "in an unaudible whisper.\n");
              return (1);
          }
          else
          {
              write("As you utter your pledge, power flows from the "+short()+
                    " and courses through your body. Your countenance grows " +
                    "terrible before your enemies.\n");
              say(QCTNAME(TP)+" utters dark words and suddenly appears stronger. " +CAP(HIS_HER(TP))+" countenance grows terrible before you.\n");
              set_alarm(195.0,0.0,&renew_pledge(TP));
              pledged = 1;
              TP->add_tmp_stat (SS_STR,3+random(3),5);
              TP->add_mana (-iPenalty);
              return (1);
          };
      }
      else if (TO->query_wielded())
      {
          write("You utter a dark pledge before the "+short()+".\n");
          say(QCTNAME(TP)+" utters dark works.\n");
          return 1;
      }
      else
      {
          write("You utter dark words before your enemies.\n");
          say(QCTNAME(TP)+" utters dark works.\n");
          return 1;
      };
    };

    return 0;
}

int do_decipher(string str)
{
  
    if (str == "engravings" || str == "dark engravings")
    {
        write("The dark engravings are beyond your comprehension.\n");
        return 1;
    }
    else
    {
        write("Decipher what?\n");
        return 1;
    }
}
/*
string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}

*/
void init_wep_recover(string arg)
{
    string tf;
    int hit, pen;

    sscanf(arg, "%s#w_wh#%d#%s", tf, hit, tf);
    sscanf(arg, "%s#w_p#%d#%s", tf, pen, tf);
    set_hit(hit);
    set_pen(pen);

    ::init_wep_recover(arg);
}

string query_wep_recover()
{
    return ::query_wep_recover() + "w_wh#" + query_hit() +
        "#w_p#" + query_pen() + "#";
}
