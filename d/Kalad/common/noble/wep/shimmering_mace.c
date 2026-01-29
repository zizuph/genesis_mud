/*
 * /d/Kalad/common/noble/wep/shimmering_mace.c
 * Purpose    : 
 * Located    : 
 * Created By : Sarr
 * Modified By: Sarr, Rico,
 * First Modif: 12.Feb.97
 *    Fysix, changed TP to query_wielded in the unwield function
 * Modified by Valen, 20010929, fixing few errors, updating functionality
 * 2017-06-04 Malus: Added club as a name 
 * 2021-11-07 Meton Changed from no-sell/why?) to keept
 */
inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

private int swinging = 0;

string lightdesc(void);

void
create_weapon()
{
    ::create_weapon();

    set_name("mace");
    add_name("club");
    set_adj(({"gleaming", "dark-green"}));
    set_pname("maces");
    set_short("gleaming dark-green mace");
    set_pshort("gleaming dark-green maces");
    set_long("The structure of this mace is rather simple. It has "+
      "a large steel ball with many round protrusions on it. However, "+
      "it is made of some strange, green-colored steel that looks so "+
      "polished it shines. The handle is wrapped with black bandages, "+
      "giving the wielder a firm grip. There is a very tiny, green "+
      "emerald at the bottom of the handle in the ball that adorns the "+
      "end of the handle.@@lightdesc@@\n");

    add_item("emerald", "You stare at the little emerald, and it "+
      "sparkles brightly for a moment.\n"+
      "You get the sudden urge to swing this mace around.\n");

    set_hit(40);
    set_pen(30);
    set_wf(TO); 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON | W_IMPALE); /* Spikes impale */

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 30, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The steel of this mace was apparently augmented with "+
	"the use of magic in its crafting.\n", 15,
	"The weight of this weapon seems to shift unusually toward "+
	"the small emerald, making it difficult for an unfamiliar "+
	"wielder.\n", 10,
	"The small emerald at the base of the handle possesses an "+
	"enchantment distinct from the mace itself.\n", 20,
	"This weapon should inflict a greater concussive force than "+
	"its weight would suggest.\n", 25,
	"The emerald is enchanted with minor light-shedding "+
	"abilities.\n", 30,
	"Swinging this weapon with sufficient skill will cause it to "+
	"emit an aura of light.\n", 45,
      }));
    add_prop(OBJ_S_WIZINFO, "This is a mace made from magically "+
      "enhanced steel. It has a special command to make it glow, "+
      "giving the area around it light. You must be skilled in club "+
      "to level 40 to wield it.\n");
    //add_prop(OBJ_M_NO_SELL, 1);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 5365);
    add_prop(OBJ_I_VOLUME, 1520);
}

void
init()
{
    ::init();

    add_action("do_swing", "swing");
}

mixed
wield(object wep)
{
    if(TP->query_skill(SS_WEP_CLUB) < 40 )
    {
	say(QCTNAME(TP)+" is not skilled enough to wield the "+
	  short() + ".\n");

	return "You are not skilled enough to manage this weapon.\n";
    }

    write("You clamp your hand around the handle of the " + short()+
      " and feel a strange tingle in your arm.\n");
    say(QCTNAME(TP) + " clamps " + HIS(TP) + " hand around the handle "+
      "of the " + short() + ".\n");

    return 1;
}

mixed
unwield(object wep)
{
    object me = query_wielded();

    me->catch_tell("You release your grip on the " + short() + ".\n");
    tell_room(environment(me), QCTNAME(me) + " releases "+
      me->query_possessive() + " grip on the " + short()+
      ".\n", ({ me }));

    return 1;
}

int
do_swing(string str)
{
    object ob;

    notify_fail("\n\tSwing what?\n\n");
    ob = present(str, TP);
    if(ob != TO)
	return 0;

//    notify_fail("\nThe " + short() + " is already glowing!\n\n");
//    if(query_prop(OBJ_I_LIGHT) == 1)
//	return 0;

    notify_fail("You do not have a good enough grip on the handle.\n");
    if(!ob->query_wielded())
	return 0;

    write("You rapidly swing the " + short() + " in circles!\n");
    say(QCTNAME(TP) + " rapidly swings the " + short() + " in "+
      "circles!\n");

    if(swinging || query_prop(OBJ_I_LIGHT) == 1) return 1;

    swinging = 1;
    set_alarm(2.0, 0.0, "swing2");

    return 1;
}

void
swing2(object ob)
{
    object tp = query_wielded();
    
    swinging = 0;

    if(!tp) return;
    
    tell_room(E(tp), "The " + short() + " begins to shimmer and glow, "+
      "casting a greenish glow around the area.\n");

    add_prop(OBJ_I_LIGHT, 1);
    
    set_adj(({"shimmering", "bright-green"}));
    set_short("shimmering bright-green mace");
    set_pshort("shimmering bright-green maces");
    set_alarm(320.0, 0.0, "dim");
}

void
dim()
{
    object ob;

    if(living(E(TO)))
    {
	ob = E(TO);

	tell_room(E(ob), "The " + short() + " dims, and the greenish "+
	  "glow fades away.\n");
    }
    else
	tell_room(E(TO), "The " + short() + " dims, and no longer glows.\n");

    remove_prop(OBJ_I_LIGHT);
    set_adj(({"gleaming", "dark-green"}));
    set_short("gleaming dark-green mace");
    set_pshort("gleaming dark-green maces");
}

string lightdesc(void)
{
 return (query_prop(OBJ_I_LIGHT) == 1) ?
  " It is shimmering with bright-green light." : "";
}
