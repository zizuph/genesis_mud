#pragma save_binary
#pragma strict_types

inherit "/std/container.c";
inherit "/lib/keep.c";
inherit "/lib/wearable_item";


#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Cirath/common/defs.h"

#define SCABBARD_SUBLOC2         "_scabbard_subloc"
#define WORN_SCABBARD            "_worn_scabbard"
static object  Worn = 0;

public void
create_container()
{
    set_name("scabbard");
    add_name("_fury_scabbard");
    set_short("leather scabbard");
    set_adj("leather");
    set_long("A valuable scabbard, probably very ancient. "
        + "It is made from wood plated with pure gold. In the "
        + "scabbard you can sheathe a sword, and from it you "
        + "can draw it again when you have to fight. You can "
        + "also wear it, and later remove it again.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(CONT_I_WEIGHT,  2000);
    add_prop(CONT_I_VOLUME,  2000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 25000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID,  0);
    add_prop(CONT_M_NO_INS, "If you want to insert a sword into the "
      + "scabbard, then try to 'sheathe' it!\n");
    add_prop(OBJ_S_WIZINFO,
        "This scabbard is the scabbard for Fury, one of the "
        +"nine elemental blades in Cirath.  It gives the wearer "
	   +"15 levels of the prop LIVE_I_SPEED.\n");
}

static int
filter_weapon(object x)
{
    return (function_exists("create_object", x) == "/std/weapon");
}

static int
filter_sword(object x)
{
    return (x->query_wt() == W_SWORD);
}

public int
do_sheathe(string str)
{
    int     result;
    object *sword,
    tp = TP;
    if (!str)
        sword = tp->query_weapon(-1);
    else
        sword = filter(FIND_STR_IN_OBJECT(str, tp),
          "filter_weapon", TO);

    sword = filter(sword, "filter_sword", TO);

    if (sizeof(sword) != 1)
    {
        NF("Sheathe which sword?\n");
        return 0;
    }

    if (sizeof(all_inventory(TO)))
    {
        NF("You cannot sheathe your "+sword[0]->short()
          + ", there is already "+LANG_ASHORT(all_inventory(TO)[0])
          + " in the "+TO->short()+".\n");
        return 0;
    }

    if ( sword[0]->query_wielded() == TP )
    {
        sword[0]->unwield_me();
        if ( sword[0]->query_wielded() == TP )
        {
            NF("You cannot unwield your "+sword[0]->short()+".\n");
            return 0;
        }
    }

    remove_prop(CONT_M_NO_INS);
    if (result = sword[0]->move(TO))
    {
        switch(result)
        {
        case 1:
            NF("Your "+sword[0]->short()+" is too heavy for the "
              + TO->short()+".\n");
            break;
        case 8:
            NF("Your "+sword[0]->short()+" is too large for the "
              + TO->short()+".\n");
            break;
        default:
            NF("Strangely, you cannot sheathe your "+sword[0]->short()
              + " in the "+ TO->short()+".\n");
            break;
        }
        return 0;
    }
    if(objectp(environment(tp)))
        environment(tp)->update_light(1);
    tp->catch_msg("You slide your "+sword[0]->short()+
        "into the leather scabbard with ease.\n");
    say(QCTNAME(TP)+" sheathes "+HIS_HER(TP)+" "
      + sword[0]->short()+".\n", tp);
    add_prop(CONT_M_NO_INS, 1);

    return 1;
}

public int
do_draw(string str)
{
    object *sword,
    tp = TP;
    mixed res;



    if (!str)
        sword = all_inventory(TO);
    else
        sword = FIND_STR_IN_OBJECT(str, TO);

    if (!sizeof(sword))
    {
        if (!str)
                  NF("Your "+TO->short()+" is empty!\n");
        else
            NF("There is no "+str+" in your "+TO->short()+"!\n");
        return 0;
    }
    tp->catch_msg("You draw your "+sword[0]->short()+" in a "
        +"single fluid motion!\n");
    say(QCTNAME(tp)+" draws "+HIS_HER(TP)+ " "
             + sword[0]->short()+".\n",TP);
    if (sword[0]->move(tp))
        sword[0]->move(tp, 1);

    if (stringp(res = sword[0]->command_wield()))
    {
        write(res);
    }

    return 1;
}

public int
do_wear(string str)
{
    object *sc,
    tp = TP;

    if (!str)
    {
        NF("Wear what?\n");
        return 0;
    }
     sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to wear the scabbard?\n");
        return 0;
    }

    if (objectp(Worn))
    {
        NF("You are already wearing it!\n");
        return 0;
    }

   if(TP->query_prop(WORN_SCABBARD) == 1)
    {
	write("You are already wearing the leather scabbard!");
	return 0;
    }

    tp->add_subloc(SCABBARD_SUBLOC2, TO);
    write("You sling the "+TO->short()+" across your back.  Energy "
        +"seems to course through your body.\n");
    say(QCTNAME(TP) + " wears the "+TO->short()+" across "
      + tp->query_possessive() + " back, an added spark in "+
      HIS_HER(TP)+ "eye.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the scabbard first!\n");
    add_prop(WORN_SCABBARD,1);
   tp->add_prop(LIVE_I_QUICKNESS,tp->query_prop(LIVE_I_QUICKNESS)+15);
    Worn = tp;
    TO->set_no_show_composite(1); /* do not display in inventory */
    return (str != "all" ? 1 : 0);
}

public int
do_remove(string str)
{
    object *sc,
    tp = TP;

    if (!str)
        return 0;

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to remove the scabbard?\n");
        return 0;
    }

    if (!objectp(Worn))
    {
        NF("You are not wearing it!\n");
        return 0;
    }

    tp->remove_subloc(SCABBARD_SUBLOC2);
    write("You remove the "+TO->short()+", feeling the mystical "
        +"energy bleed from you.\n");
    say(QCTNAME(TP) + " removes the "+TO->short()+" with a look "
        +"of fatigue.\n");
  tp->add_prop(LIVE_I_QUICKNESS,tp->query_prop(LIVE_I_QUICKNESS)-15);
    remove_prop(WORN_SCABBARD);
    remove_prop(OBJ_M_NO_DROP);
    Worn = 0;
    TO->set_no_show_composite(0);  /* display in inventory again */
    return (str != "all" ? 1 : 0);
}

public void
enter_env(object dest, object old)
{
    string  msg;

    ::enter_env(dest, old);

    if (!objectp(old) || !objectp(dest) || !interactive(dest))
        return;

    setuid();
    seteuid(getuid());
}

public void
leave_env(object old, object dest)
{
    string  msg;

    TP->remove_subloc(SCABBARD_SUBLOC2);
    TO->unset_no_show_composite();
    remove_prop(OBJ_M_NO_DROP);

    ::leave_env(old, dest);

    if (!objectp(dest) || !objectp(old) || !interactive(old))
        return;

    setuid();
    seteuid(getuid());
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if(subloc == SCABBARD_SUBLOC2)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) +
            " is wearing "+LANG_ASHORT(TO)+" across " +
       HIS_HER(TP) +" back.\n";
        else
            data = "You are wearing a "+LANG_ASHORT(TO)+
            " across your back.\n";
        return data;
    }
    return 0;
}

public int query_recover() { return 0; }

void
init()
{
    ::init();

    add_action(do_sheathe, "sheathe");
    add_action(do_draw,    "draw");
    add_action(do_wear,    "wear");
    add_action(do_remove,  "remove");
}

public object
query_worn()
{
    return Worn;
}


