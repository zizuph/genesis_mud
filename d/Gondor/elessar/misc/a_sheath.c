inherit "/std/container";
 
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
 
#include "/d/Gondor/defs.h"
 
#define SHEATH_SUBLOC		"_sheath_subloc"
 
int     worn = 0;
 
void
create_container()
{
    set_name("sheath");
    add_name("scabbard");
    set_short("rune-adorned sword-sheath");
    set_adj(({"golden", "silver","sword","adorned"}));
    set_long(BSN("A sheath made to fit a long sword. " +
	"It is overlaid with a tracery of flowers and leaves wrought " +
	"of silver and gold, and on it are set in elven runes formed " +
	"of many gems the name Anduril and the lineage of the sword."));
 
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT,  2000);
    add_prop(CONT_I_VOLUME,  2000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 25000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID,  0);
    add_prop(CONT_M_NO_INS, "If you want to insert a sword into the "
                          + "sheath, then try to 'sheathe' it!\n");
    add_prop(OBJ_S_WIZINFO, BSN(
	"This sheath was made by Celeborn and Galadriel in Lorien, " +
	"as a parting to the leader of the Fellowship of the Ring, " +
	"Aragorn, and it was made to fit his sword, Anduril, the " +
	"Flame of the West, the Sword of Elendil reforged. "
	));
}
 
void
init()
{
    ::init();
 
    add_action("do_sheathe", "sheathe");
    add_action("do_draw",    "draw");
    add_action("do_wear",    "wear");
    add_action("do_remove",  "remove");
}
 
int
filter_weapon(object x)
{
    return (function_exists("create_object", x) == "/std/weapon");
}
 
int
filter_sword(object x)
{
    return (x->query_wt() == W_SWORD);
}
 
int
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
    tp->catch_msg("You sheathe your "+sword[0]->short()+".\n");
    tell_room(ENV(tp), QCTNAME(tp)+" sheathes "+POSSESSIVE(tp)+" "
      + sword[0]->short()+".\n", tp);
    add_prop(CONT_M_NO_INS, 1);
 
    return 1;
}
 
int
do_draw(string str)
{
    object *sword,
            tp = TP;
 
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
    tp->catch_msg("You draw your "+sword[0]->short()+"!\n");
    tell_room(ENV(tp), QCTNAME(tp)+" draws "+POSSESSIVE(tp)+ " "
      + sword[0]->short()+".\n", tp);
    if (sword[0]->move(tp))
        sword[0]->move(tp, 1);
    sword[0]->wield_wep(sword[0]->query_name());
    return 1;
}
 
string
query_auto_load()
{
    return MASTER + ":";
}
 
int
do_wear(string str)
{
    object *sc,
            tp = TP;
 
    if (!str)
        return 0;
 
    sc = FIND_STR_IN_OBJECT(str, tp);
 
    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to wear the sheath?\n");
        return 0;
    }
 
    if (worn)
    {
        NF("You are already wearing it!\n");
        return 0;
    }
  
    if (member_array(SHEATH_SUBLOC, tp->query_sublocs()) > -1)
    { 
       NF("You already wear another sheath!\n");
       return 0;
    } 
 
    tp->add_subloc(SHEATH_SUBLOC, TO);
    write("You wear the "+TO->short()+" around your hips.\n");
    say(QCTNAME(TP) + " wears the "+TO->short()+" around "
      + tp->query_possessive() + " hips.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the sheath first!\n");
    worn = 1;
    TO->set_no_show_composite(1); /*do not display in inventory */
    return 1;
}
 
int
do_remove(string str)
{
    object *sc,
            tp = TP;
 
    if (!str)
        return 0;
 
    sc = FIND_STR_IN_OBJECT(str, tp);
 
    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to remove the sheath?\n");
        return 0;
    }
 
    if (!worn)
    {
        NF("You are not wearing it!\n");
        return 0;
    }
 
    tp->remove_subloc(SHEATH_SUBLOC);
    write("You remove the "+TO->short()+".\n");
    say(QCTNAME(TP) + " removes the "+TO->short()+".\n");
    remove_prop(OBJ_M_NO_DROP);
    worn = 0;
    TO->set_no_show_composite(0);  /* display in inventory again */
    return 1;
}
 
void
leave_env(object dest, object old)
{
    TP->remove_subloc(SHEATH_SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    ::leave_env(dest, old);
}
 
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
 
    if(subloc == SHEATH_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + 
                " is wearing "+LANG_ASHORT(TO)+".\n";
        else
            data = "You are wearing "+LANG_ASHORT(TO)+".\n";
        return data;
    }
    return 0;
}
 
public int query_recover() { return 0; }
