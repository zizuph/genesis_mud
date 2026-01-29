inherit "/std/container";
inherit "/lib/wearable_item";
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include <wa_types.h>

#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/knight_scabbard.c
 * Purpose    : This is the pair of scabbards for the Death Knights 
 *              of the Khiraa. A guild object.
 * Located    : Can get it from the training room.
 * Created By : Sarr 17.Mar.97
 * Modified By: Sarr 3.Jul.98 (recode)
 */



#define DK_SCABBARD_ONE  "_dk_scabbard_one"
#define DK_SCABBARD_TWO  "_dk_scabbard_two"

int is_full();
object* get_swords();

int worn;
string Gowner = "Khiraa";

void
set_owner(string str)
{
    Gowner = str;
}

string
query_own()
{
    return Gowner;
}

int
is_full()
{
    object *obs;
    obs = all_inventory(TO);
    if(sizeof(obs) > 1)
        return 1;        
    return 0;
}

object*
get_swords()
{
    int i;
    object *obs,sword_one,sword_two;
    obs = all_inventory(TO);
    for(i=0;i<sizeof(obs);i++)
    {
        if(obs[i]->query_prop(DK_SCABBARD_ONE))
            sword_one = obs[i];
        if(obs[i]->query_prop(DK_SCABBARD_TWO))
            sword_two = obs[i];
    }
    return ({sword_one,sword_two});
}



void
create_container()
{
    set_name("scabbards");
    add_name("_dk_scab_");
    set_adj("midnight-black");
    add_adj("skull-adorned");
    set_pshort("pairs of midnight-black skull-adorned scabbards");
    set_short("pair of midnight-black skull-adorned scabbards");
    set_long("These two scabbards are made of some type of blackened "+
    "steel and are decorated with miniture grim looking skulls. "+
    "Cryptic blood-red runes are inscribed along its sides. They "+
    "are crossed over eachother hand held together by black leather "+
    "straps that can be fitted over your back. You also see the words "+
    "'@@query_own@@' and 'help scabbard' on it.\n");

    config_wearable_item(A_BACK, 1, 8);

    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_VOLUME,970);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_I_MAX_VOLUME,80000);
    add_prop(OBJ_M_NO_DROP, "The scabbards are too valuable " +
        "to be dropped!\n");
}

void
init()
{
    ::init();
    add_action("do_help","help");
    add_action("do_sheath","sheath");
    add_action("do_sheathr","sheathr");
    add_action("do_sheathl","sheathl");
    add_action("do_sheathb","sheathb");
    add_action("do_draw1","draw1");
    add_action("do_draw2","draw2");
    add_action("do_drawb","drawb");
    add_action("do_put","put");
    add_action("do_put","drop");
}

int
do_help(string str)
{
    if(str != "scabbard")
        return 0;
    write("You can do the following commands:\n"+
          "sheath    -  This will sheath any sword you provide a name for.\n"+
          "sheathr   -  This will sheath the sword in your right hand.\n"+
          "sheathl   -  This will sheath the sword in your left hand.\n"+
          "sheathb   -  This will sheath both swords in your hands.\n"+
          "draw1     -  This will draw the sword in the first scabbard,\n"+
          "               which will be the one you sheathed first.\n"+
          "draw2     -  This will draw the sword in the second scabbard,\n"+
          "               which will be the one you sheathed second.\n"+
          "drawb     -  This will attempt to draw both swords in the\n"+
          "               scabbards and wield them both.\n"+
          "wear      -  Wear the scabbards on your back.\n"+
          "remove    -  Remove the scabbards from your back.\n");
    return 1;
}

int
do_put(string str)
{
    string ver;
    object sca,ob;
    ver = query_verb();
    if(parse_command(ver+" "+str,TP,"'"+ver+"' %o 'in' %o",ob,sca))
    {
        if(sca == TO)
        {
            write("If you want to put a sword in the sheath, try "+
            "'help scabbard'.\n");
            return 1;
        }
    }
}


int 
do_sheath(string arg)
{
    string ws;
    object sword,*slots_free;
    NF("Sheathe what sword?\n");
    if(!parse_command("sheath "+arg,TP,"'sheath' %o",sword))
        return 0;
    if(!sword)
        return 0;
    NF("You must have the "+sword->short()+" first!\n");
    if(!present(sword,TP))
        return 0;
    NF("You can only put swords in here!\n");
    if(sword->query_wt() != W_SWORD && sword->query_pen())
        return 0;
    NF("You're scabbards are already full!\n");
    if(is_full())
        return 0;
    slots_free = get_swords();
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        sword->add_prop(DK_SCABBARD_ONE,1);
    }
    else
    {
        ws = "second";
        sword->add_prop(DK_SCABBARD_TWO,1);
    }
    if(sword->query_wielded())
        sword->unwield_me();
    NF("It doesn't fit.\n");
    if(sword->move(TO))
        return 0;
    write("You slide your "+sword->short()+" into your "+ws+" midnight-black "+
    "skull-adorned scabbard.\n");
    say(QCTNAME(TP)+" slides "+HIS(TP)+" "+sword->short()+" into one of "+
    HIS(TP)+" midnight-black skull-adorned scabbards.\n");
    return 1;
}

int 
do_sheathr(int i)
{
    string ws;
    object sword,*slots_free;
    NF("You are not wielding a sword in your right hand.\n");
    sword = TP->query_weapon(W_RIGHT);
    if(!objectp(sword))
        return 0;
    if(sword->query_wt() != W_SWORD && sword->query_pen())
        return 0;
    NF("You're scabbards are already full!\n");
    if(is_full())
        return 0;
    slots_free = get_swords();
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        sword->add_prop(DK_SCABBARD_ONE,1);
    }
    else
    {
        sword->add_prop(DK_SCABBARD_TWO,1);
        ws = "second";
    }
    sword->unwield_me();
    NF("It doesn't fit.\n");
    if(sword->move(TO))
        return 0;
    if(i == 1)
        return 1;
    write("You slide your "+sword->short()+" into your "+ws+" midnight-black "+
    "skull-adorned scabbard.\n");
    say(QCTNAME(TP)+" slides "+HIS(TP)+" "+sword->short()+" into one of "+
    HIS(TP)+" midnight-black skull-adorned scabbards.\n");
    return 1;
}

int 
do_sheathl(int i)
{
    string ws;
    object sword,*slots_free;
    NF("You are not wielding a sword in your left hand.\n");
    sword = TP->query_weapon(W_LEFT);
    if(!objectp(sword))
        return 0;
    if(sword->query_wt() != W_SWORD && sword->query_pen())
        return 0;
    NF("You're scabbards are already full!\n");
    if(is_full())
        return 0;
    slots_free = get_swords();
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        sword->add_prop(DK_SCABBARD_ONE,1);
    }
    else
    {
        ws = "second";
        sword->add_prop(DK_SCABBARD_TWO,1);
    }
    sword->unwield_me();
    NF("It doesn't fit.\n");
    if(sword->move(TO))
        return 0;
    if(i == 1)
        return 1;
    write("You slide your "+sword->short()+" into your "+ws+" midnight-black "+
    "skull-adorned scabbard.\n");
    say(QCTNAME(TP)+" slides "+HIS(TP)+" "+sword->short()+" into one of "+
    HIS(TP)+" midnight-black skull-adorned scabbards.\n");
    return 1;
}

int 
do_sheathb()
{
    object rsword,lsword,*slots_free;
    NF("You are not wielding a sword in your left hand.\n");
    lsword = TP->query_weapon(W_LEFT);
    if(!objectp(lsword))
        return 0;
    if(lsword->query_wt() != W_SWORD && lsword->query_pen())
        return 0;
    NF("You are not wielding a sword in your right hand.\n");
    rsword = TP->query_weapon(W_RIGHT);
    if(!objectp(rsword))
        return 0;
    if(rsword->query_wt() != W_SWORD && rsword->query_pen())
        return 0;
    NF("You're scabbards are already full!\n");
    if(is_full())
        return 0;
    slots_free = get_swords();
    NF("There is already a sword in one of your scabbards. You can't "+
    "do this command.\n");
    if(objectp(slots_free[0]) || objectp(slots_free[1]))
        return 0;
    NF("Something went wrong.\n");
    if(!do_sheathr(1))
        return 0;
    if(!do_sheathl(1))
        return 0;
    write("You slide your "+rsword->short()+" and "+lsword->short()+
    " into your "+short()+".\n");
    say(QCTNAME(TP)+" slides "+HIS(TP)+" "+rsword->short()+" and "+
    lsword->short()+" into "+HIS(TP)+" "+short()+".\n");
    return 1;
}

int
do_draw1(int i)
{
    object sword,*swords;
    swords = get_swords();
    sword = swords[0];
    NF("There isn't a sword in the first scabbard!\n"); 
    if(!objectp(sword))
        return 0;
    NF("You couldn't draw it for some reason.\n");
    if(sword->move(TP))
        return 0;
    if(i != 1)
    {
    write("You draw your "+sword->short()+" from your first scabbard!\n");
    say(QCTNAME(TP)+" draws "+HIS(TP)+" "+sword->short()+"!\n");
    }
    sword->command_wield();
    return 1;
}

int
do_draw2(int i)
{
    object sword,*swords;
    swords = get_swords();
    sword = swords[1];
    NF("There isn't a sword in the second scabbard!\n"); 
    if(!objectp(sword))
        return 0;
    NF("You couldn't draw it for some reason.\n");
    if(sword->move(TP))
        return 0;
    if(i != 1)
    {
    write("You draw your "+sword->short()+" from your second scabbard!\n");
    say(QCTNAME(TP)+" draws "+HIS(TP)+" "+sword->short()+"!\n");
    }
    sword->command_wield();
    return 1;
}

int
do_drawb()
{
    object sword1,sword2,*swords;
    swords = get_swords();
    sword1 = swords[0];
    sword2 = swords[1];
    NF("There is not two swords in the scabbard!\n"); 
    if(!objectp(sword1) || !objectp(sword2))
        return 0;
    NF("You could not draw it for some reason.\n");
    write("You draw your "+sword1->short()+" and "+sword2->short()+
    " from your "+short()+".\n");
    say(QCTNAME(TP)+" draws "+HIS(TP)+" "+sword1->short()+" and "+
    sword2->short()+" from "+HIS(TP)+" "+short()+".\n");
    if(!do_draw1(1))
        return 0;
    if(!do_draw2(1))
        return 0;
    return 1;
}
