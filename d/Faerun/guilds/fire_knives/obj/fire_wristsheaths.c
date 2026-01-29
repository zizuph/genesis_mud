inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";
#include <wa_types.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>

#pragma strict_types
#pragma save_binary


#define FIRE_WRISTSHEAT_ONE  "_fire_wristsheat_one"
#define FIRE_WRISTSHEAT_TWO  "_fire_wristcheat_two"

#define NO_SELL_VBFC &no_sell_vbfc()

int is_full();

object* get_knives();


int worn;
string Gowner = "Fire Knives";


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
    obs = all_inventory(this_object());
    
    if(sizeof(obs) > 1)
        return 1;   
    
    return 0;
}


object*
get_knives()
{
    int i;
    object *obs, knife_one, knife_two;
    
    obs = all_inventory(this_object());
    
    for(i=0;i<sizeof(obs);i++)
    {
        if(obs[i]->query_prop(FIRE_WRISTSHEAT_ONE))
            knife_one = obs[i];
        
        if(obs[i]->query_prop(FIRE_WRISTSHEAT_TWO))
            knife_two = obs[i];
    }
    
    return ({knife_one, knife_two});
}


void
create_container()
{
    set_name("wristsheaths");
    add_name("wristsheath");
	add_name("sheath");
	add_name("sheaths");
    add_name("_fireknives_wristsheath_");
    
    set_adj("midnight-black");
    add_adj("skull-adorned");
    
    set_short("pair of jet-black leather wristsheaths");
    set_pshort("pairs of jet-black leather wristsheaths");
   
    set_long("These two sheaths are made of thick black leather "+
        "without any special adornment or indications of their "+
        "particularity. Practically undifferentiated from any "+
        "other by virtue of their appearance, their difference "+
        "found more in their capacity to deafen the sound of a "+
        "blade entering or exiting while also being devoid of "+
        "any special creaking sounds so typical in others. "+
        "Each one of them go on each opposite side of the intended "+
        "body part. You also see the words "+
        "'@@query_own@@' and 'wristhelp wristsheaths' on it.\n");

    config_wearable_item(A_WRISTS, 1, 8);

    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_VOLUME,970);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_I_MAX_VOLUME,80000);
    add_prop(OBJ_I_VALUE, 4000);
    //add_prop(OBJ_M_NO_DROP, "The wristsheats are too valuable " +
      //  "to be dropped!\n");
      
    set_keep(1);
}


void
init()
{
    ::init();
    add_action("do_wristhelp","wristhelp");
    add_action("do_wristsheath","wristsheath");
    add_action("do_wristsheathr","wristsheathr");
    add_action("do_wristsheathl","wristsheathl");
    add_action("do_wristsheathb","wristsheathb");
    add_action("do_wristdraw1","wristdraw1");
    add_action("do_wristdraw2","wristdraw2");
    add_action("do_wristdrawb","wristdrawb");
    add_action("do_wristput","wristput");
    add_action("do_wristput","wristdrop");
}


int
do_wristhelp(string str)
{
    if(str != "wristsheaths")
        return 0;
    
    write("You can do the following commands:\n"+
          "wristsheath    -  This will sheath any knife you provide a name for.\n"+
          "wristsheathr   -  This will sheath the knife in your right hand.\n"+
          "wristsheathl   -  This will sheath the knife in your left hand.\n"+
          "wristsheathb   -  This will sheath both knifes in your hands.\n"+
          "wristdraw1     -  This will draw the knife in the first wristsheath,\n"+
          "                  which will be the one you sheathed first.\n"+
          "wristdraw2     -  This will draw the knife in the second wristsheath,\n"+
          "                  which will be the one you sheathed second.\n"+
          "wristdrawb     -  This will attempt to draw both knifes in the\n"+
          "                  wristsheath and wield them both.\n"+
          "wear           -  Wear the wristsheath on your wrists.\n"+
          "remove         -  Remove the wristsheath from your wrists.\n");
    return 1;
}


int
do_wristput(string str)
{
    string ver;
    object sca,ob;
    
    ver = query_verb();
    
    if(parse_command(ver+" "+str,this_player(),"'"+ver+"' %o 'in' %o",ob,sca))
    {
        if(sca == this_object())
        {
            write("If you want to put a knife in the wristsheath, try "+
            "'help wristsheaths'.\n");
            return 1;
        }
    }
}


int 
do_wristsheath(string arg)
{
    string ws;
    object knife,*slots_free;
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"sheathe weapons in them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    notify_fail("Sheathe what knife?\n");
    if(!parse_command("wristsheath "+arg,this_player(),"'sheath' %o",knife))
        return 0;
    
    if(!knife)
        return 0;
    
    notify_fail("You must have the "+knife->short()+" first!\n");
    if(!present(knife,this_player()))
        return 0;
    
    notify_fail("You can only put knifes in here!\n");
    if(knife->query_wt() != W_KNIFE && knife->query_pen())
        return 0;
    
    notify_fail("Your wristsheaths are already full!\n");
    if(is_full())
        return 0;
    
    slots_free = get_knives();
    
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        knife->add_prop(FIRE_WRISTSHEAT_ONE,1);
    }
    else
    {
        ws = "second";
        knife->add_prop(FIRE_WRISTSHEAT_TWO,1);
    }
    
    if(knife->query_wielded())
        knife->unwield_me();
    
    notify_fail("It doesn't fit.\n");
    if(knife->move(this_object()))
        return 0;
    
    write("You slide your "+knife->short()+" into one of your "+ws+" jet-black leather wristsheaths.\n");
    
    say(QCTNAME(this_player())+" slides "+this_player()->query_possessive()+" "+knife->short()+" into one of "+
    this_player()->query_possessive()+" jet-black leather wristsheaths.\n");
    return 1;
}


int 
do_wristsheathr(int i)
{
    string ws;
    object knife,*slots_free;
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"sheathe weapons in them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    notify_fail("You are not wielding a knife in your right hand.\n");
    
    knife = this_player()->query_weapon(W_RIGHT);
    
    if(!objectp(knife))
        return 0;
    
    if(knife->query_wt() != W_KNIFE && knife->query_pen())
        return 0;
    
    notify_fail("You're scabbards are already full!\n");
    if(is_full())
        return 0;
    
    slots_free = get_knives();
    
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        knife->add_prop(FIRE_WRISTSHEAT_ONE,1);
    }
    else
    {
        knife->add_prop(FIRE_WRISTSHEAT_TWO,1);
        ws = "second";
    }
    
    knife->unwield_me();
    
    notify_fail("It doesn't fit.\n");
    if(knife->move(this_object()))
        return 0;
    
    if(i == 1)
        return 1;
    
    write("You slide your "+knife->short()+" into your "+ws+" jet-black leather wristsheath.\n");
    
    say(QCTNAME(this_player())+" slides "+this_player()->query_possessive()+" "+knife->short()+" into one of "+
    this_player()->query_possessive()+" jet-black leather wristsheaths.\n");
    
    return 1;
}


int 
do_wristsheathl(int i)
{
    string ws;
    object knife,*slots_free;
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"sheathe weapons in them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    notify_fail("You are not wielding a knife in your left hand.\n");
    
    knife = this_player()->query_weapon(W_LEFT);
    if(!objectp(knife))
        return 0;
    
    if(knife->query_wt() != W_KNIFE && knife->query_pen())
        return 0;
    
    notify_fail("Your wristsheaths are already full!\n");
    if(is_full())
        return 0;
    
    slots_free = get_knives();
    if(!objectp(slots_free[0]))
    {
        ws = "first";
        knife->add_prop(FIRE_WRISTSHEAT_ONE,1);
    }
    else
    {
        ws = "second";
        knife->add_prop(FIRE_WRISTSHEAT_TWO,1);
    }
    
    knife->unwield_me();
    
    notify_fail("It doesn't fit.\n");
    if(knife->move(this_object()))
        return 0;
    
    if(i == 1)
        return 1;
    
    write("You slide your "+knife->short()+" into your "+ws+" jet-black leather wristsheath.\n");
    
    say(QCTNAME(this_player())+" slides "+this_player()->query_possessive()+" "+knife->short()+" into one of "+
    this_player()->query_possessive()+" jet-black leather wristsheaths.\n");
    
    return 1;
}


int 
do_wristsheathb()
{
    object rknife,lknife,*slots_free;
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"sheathe weapons in them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    notify_fail("You are not wielding a knife in your left hand.\n");
    
    lknife = this_player()->query_weapon(W_LEFT);
    if(!objectp(lknife))
        return 0;
    
    if(lknife->query_wt() != W_KNIFE && lknife->query_pen())
        return 0;
    
    notify_fail("You are not wielding a knife in your right hand.\n");
    
    rknife = this_player()->query_weapon(W_RIGHT);
    if(!objectp(rknife))
        return 0;
    
    if(rknife->query_wt() != W_KNIFE && rknife->query_pen())
        return 0;
    
    notify_fail("Your wristsheaths are already full!\n");
    if(is_full())
        return 0;
    
    slots_free = get_knives();
    notify_fail("There is already a knife in one of your wristsheaths. You can't "+
    "do this command.\n");
    
    if(objectp(slots_free[0]) || objectp(slots_free[1]))
        return 0;
    
    notify_fail("Something went wrong.\n");
    if(!do_wristsheathr(1))
        return 0;
    
    if(!do_wristsheathl(1))
        return 0;
    
    write("You slide your "+rknife->short()+" and "+lknife->short()+
    " into your "+short()+".\n");
    
    say(QCTNAME(this_player())+" slides "+this_player()->query_possessive()+" "+rknife->short()+" and "+
    lknife->short()+" into "+this_player()->query_possessive()+" jet-black leather wristsheath.\n");
    
    return 1;
}


int
do_wristdraw1(int i)
{
    object knife,*knifes;
    knifes = get_knives();
    knife = knifes[0];
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"draw weapons from them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    notify_fail("There isn't a knife in the first wristsheath!\n"); 
    if(!objectp(knife))
        return 0;
    
    notify_fail("You couldn't draw it for some reason.\n");
    if(knife->move(this_player()))
        return 0;
    
    if(i != 1)
    {
        write("You draw your "+knife->short()+" from your first wristsheath!\n");
        say(QCTNAME(this_player())+" draws "+this_player()->query_possessive()+" "+knife->short()+"!\n");
    }
    
    knife->command_wield();
    
    return 1;
}


int
do_wristdraw2(int i)
{
    object knife,*knifes;
    knifes = get_knives();
    knife = knifes[1];
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"draw weapons from them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
    
    
    notify_fail("There isn't a knife in the second wristsheath!\n"); 
    if(!objectp(knife))
        return 0;
    
    notify_fail("You couldn't draw it for some reason.\n");
    if(knife->move(this_player()))
        return 0;
    
    if(i != 1)
    {
        write("You draw your "+knife->short()+" from your second wristsheath!\n");
        say(QCTNAME(this_player())+" draws "+this_player()->query_possessive()+" "+knife->short()+"!\n");
    }
    
    knife->command_wield();
    
    return 1;
}


int
do_wristdrawb()
{
    object knife1,knife2,*knifes;
    knifes = get_knives();
    knife1 = knifes[0];
    knife2 = knifes[1];
    
    notify_fail("You need to wear the "+short()+" in order to "
    +"draw weapons from them.\n");
    if (this_object()->query_worn() == 0)
    {
        return 0;
    }
     
    notify_fail("There are not two knifes in the wristsheaths!\n"); 
    if(!objectp(knife1) || !objectp(knife2))
        return 0;
    
    notify_fail("You could not draw it for some reason.\n");
    write("You draw your "+knife1->short()+" and "+knife2->short()+
    " from your jet-black leather wristsheath.\n");
    
    say(QCTNAME(this_player())+" draws "+this_player()->query_possessive()+" "+knife1->short()+" and "+
    knife2->short()+" from "+this_player()->query_possessive()+" jet-black leather wristsheath.\n");
    
    if(!do_wristdraw1(1))
        return 0;
    
    if(!do_wristdraw2(1))
        return 0;
    
    return 1;
}

/*
 * Function name: no_sell_vbfc
 * Description  : VBFC for OBJ_M_NO_SELL
 * Returns      : int -- 0 if may be sold or
 *                string -- msg if may not be sold
 */
public mixed
no_sell_vbfc()
{
    if (sizeof(all_inventory(this_object())))
    {
        return ("The " + query_name() + " is not empty at the "
          + "moment. Please empty it before you sell it, to "
          + "prevent loss of knives or daggers.\n");
    }
    return 0;
}



/*
 * Function name: set_keep
 * Description  : mask parent to prevent selling non-empty pack
 * Arguments    : int keep -- whether or not to keep
 */
public void
set_keep(int keep = 1)
{
    if (keep)
    {
        ::set_keep(keep);
        return;
    }
    add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
}


/*
 * Function name: query_keep
 * Description  : query current 'keep' status
 * Returns      : int -- 1 if keep protected, 0 if not
 */
public int
query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != NO_SELL_VBFC);
}


/*
 * Function name: query_recover
 * Description  : check whether pack is recoverable (it is)
 * Returns      : string -- the recovery string
 */
public string
query_recover()
{
    return MASTER + ":"  + query_keep_recover();
     return MASTER + ":" + query_keep_recover();
}


/*
 * Function name: init_recover
 * Description  : set the recovery vars
 * Arguments    : string arg -- the arguments to parse
 */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
    //init_container_recover(arg);
}


/*
 * Function name: tmp_add_prop
 * Description  : add OBJ_M_NO_DROP prop again
 * Arguments    : mixed setting -- value of OBJ_M_NO_DROP
 *                object tp -- this_player
 */
public void
tmp_add_prop(mixed setting, object tp)
{
    /* Add prop only if backpack is still in player's inventory */
    if (objectp(tp) && objectp(environment(this_object())) && (tp == environment(this_object())))
    {
        add_prop(OBJ_M_NO_DROP, setting);
    }
}


/*
 * Function name: query_auto_load
 * Description  : remove the OBJ_M_NO_DROP property if it is set so the
 *                backpack and its contents are not lost when player quits.
 * Returns      : 0 -- doesn't autoload
 */
public string
query_auto_load()
{
    mixed setting;
    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        set_alarm(0.1, 0.0, &tmp_add_prop(setting, environment(this_object())));
    }
    return 0;
}
