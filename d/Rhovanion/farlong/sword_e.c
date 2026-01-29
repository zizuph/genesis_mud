inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define TP this_player()

string owner;

void
create_weapon()
{
   set_name("katana");
   add_name("_final_quest_sword_");
   set_short("kregora katana");
   set_long(break_string("This beauitiful blade, was fashioned with sweat "+
        "and toil, magic and soul having gone into it's shimmering black "+
        "blade. The edge is the sharpest you have ever seen, enough to "+
        "slice a man straight through.\n",76));
   set_adj("kregora");
   
   set_default_weapon(56, 58, W_SWORD, W_SLASH | W_IMPALE,  
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 13560); 
   add_prop(OBJ_I_VOLUME,  1100); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(56, 58) + random(150) - 65);
   add_prop(OBJ_M_NO_BUY, 1);

   add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ 
        ({ 100, break_string("This katana has the ability to blind in "+
	"combat, use it carefully. The power cannot be controlled and "+
	"you have no idea when it will blind.\n", 76) }),
        ({ 80, break_string("This katana almost hums in your palm, you "+
	"can feel power running through the magical curved blade. It "+
	"will deliver powerful stunning blows and can even blind in "+
	"some situations.\n", 76) }),
        ({ 60, break_string("Darkness will be visiting some of your foes "+
	"if they are not careful, this katana is a deadly weapon indeed.\n", 76) }),
        ({ 40, break_string("The katana's blade hums with power, innate "+
	"and contained. You think that it can deliver a stunning blow so "+
	"powerful that it will render the enemy in darkness.\n", 76) }),
        ({ 20, break_string("This is a terrible weapon and you can almost "+
	"feel the power coursing through the blade. You think that "+
	"it may have a special attack somehow.\n", 76) }), })
        );
   add_prop(OBJ_S_WIZINFO, break_string("This is the katana obtained "+
	"from the katana quest in Emerald. It is forged is "+
	"/d/Emerald/mylos/vamp/l4.c and can only be forged once. It "+
	"has a special attack that can blind people with a random "+
	"value.\n", 76));
}

public int
wield(object wep)
{
   if (TP->query_skill(SS_WEP_SWORD)<60 || TP->query_real_name()!=owner)
   {
      write("Something within the sword resists you.\n");
      return -1;
   }
   if(TP->query_alignment() >= 0)
   {
        write("Something within the sword repels you.\n");
        return -1;
   }
   return 0;
}

string
query_recover()
{
   return MASTER + ":" + query_wep_recover() + "##owner#" + owner + "##";
}
void
init_recover(string arg)
{
   init_wep_recover(arg);
    sscanf(arg, "##owner#%s##", owner);
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
        query_wielded()->catch_msg("The kregora katana slices near to "+
                QTNAME(enemy)+"'s body.\n");
        enemy->catch_msg("The kregora katana slices near to your body.\n");
    }
    else if (phurt == 0)
    {
        query_wielded()->catch_msg("You snarl in glee as the katana just "+
                "grazes " + QTNAME(enemy) + ".\n");
        enemy->catch_msg("The kregora katana grazes you as it passes "+
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

void
set_owner(string str)
{
    owner = str;
}
