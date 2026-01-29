inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define TP this_player()

void
create_weapon()
{
   set_name("katana");
   add_name("_final_quest_sword_");
   set_short("adamant katana");
   set_long(break_string("An adamantine blade, fashioned by sweat "+
        "and toil, and soul and blood. It looks like it would sever "+
        "a man in two, the blade is so sharp. Runes run along the length "+
        "of the blade, glowing slightly with a power that feeds the "+
        "blade.\n",76));
   set_adj("adamant");
   
   set_default_weapon(56, 58, W_SWORD, W_SLASH | W_IMPALE,  
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 13560); 
   add_prop(OBJ_I_VOLUME,  1100); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(56, 58) + random(150) - 65);
   add_prop(OBJ_M_NO_BUY, 1);
}

public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_SWORD) < 60)
   {
      write("Something within the sword resists you.\n");
      return -1;
   }
   if(TP->query_alignment() <= 0)
   {
        write("Something within the sword repels you.\n");
        return -1;
   }
   return 0;
}

string
query_recover()
{
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg)
{
   init_wep_recover(arg);
}


int
try_hit(object ob) 
{
   return 1; 
}

/* After we tried to hit something this function is called with the result. */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object blind;

    if (phurt == -1)
    {
        query_wielded()->catch_msg("The adamant katana slices near to "+
                QTNAME(enemy)+"'s body.\n");
        enemy->catch_msg("The adamant katana slices near to your body.\n");
    }
    else if (phurt == 0)
    {
        query_wielded()->catch_msg("You snarl in glee as the katana just "+
                "grazes " + QTNAME(enemy) + ".\n");
        enemy->catch_msg("The adamant katana grazes you as it passes "+
                "very closely by you.\n");
    }
    else
    {
	if(!random(11) && !present("_sword_blind_", enemy))
        {
           query_wielded()->catch_msg("The katana crackles with energy as it "+
              "hits, and "+QTNAME(enemy)+"'s world fades away.\n");
           enemy->catch_msg("You feel surprised as the katana hits you, and "+
                "the world goes black.\n");
           if(!present("_sword_blind_", enemy))
           {
              setuid();
              seteuid(getuid());
              blind = clone_object("/d/Emerald/mylos/vamp/blind");
              blind->move(enemy, 1);
           }
           return 0;
        }
        return 0;
    }
    return 0;
}
