/* coffin.c created by Novo 
 *
 * This is the standard resting place for a vampire.
 *
 */

#pragma save_binary

inherit "/std/receptacle";
inherit "/lib/guild_support";
inherit "/lib/commands";

#include "../guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <std.h>

#define COFFIN_OWNER(x) (owner==x->query_real_name())

int on_fire=0;
int burn_level=0;
string arsonist;
string destroyer;

string owner;
string lining;
string lining_color;
string material="wood";
int material_cost;
string cost_desc;
string carving;

public void set_material_cost(int i);
public void set_material(string m);
public void surprise_vampire(object vampire,string destroyer);
public void closed_from_outside();
public void checkempty();

void
create_receptacle()
{
    set_name( ({ "coffin", "vamp_coffin" }) );
    
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(CONT_I_CLOSED,closed_from_outside);
    add_prop(OBJ_M_NO_GET,checkempty);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(CONT_I_VOLUME,50000);

    add_prop(ROOM_I_NO_THIRST,1);

    remove_prop(ROOM_I_LIGHT);
    add_prop("_room_s_light_desc", "Darkness soothes your mind and " +
	"rests your eyes.\n");
	
	add_prop(ROOM_S_DARK_LONG,"A dark place.\n");
  
    add_prop(OBJ_S_WIZINFO, "If a coffin is buggy and preventing a " +
        "player from logging in, simply remove it.  The player should " +
        "then be able to log in successfully.  Please notify the " +
        "guildmaster and domain liege of any such bugs.\n");

	add_prop(OBJ_M_NO_SELL,"Coffins are custom built for the intended "+
	    "owner.\n");
 
    create_guild_support();
    
    set_material_cost(0);
    set_material(material);
    set_cf(TO);

    setuid();
    seteuid(getuid());
}

void
set_owner(string who)
{
    string posname = LANG_POSS(who);

    if (posname != (who + "'s"))
    {
        // This is probably a common misspelling, so we'll add it.
        add_name(who + "'s coffin");
    }

    add_name(posname + " coffin");
    owner=who;
    
}

public int closed_from_outside()
{
    if (!IS_CLONE)
    {
        return 0;
    }
    if (ENV(TP)==TO)
    {
        return 0;
    }
    int i=0;
    while (previous_object(i))
    {
        if (MASTER_OB(previous_object(i))==OWN_STATUE)
        {
            return 0;
        }
        i--;
    }
    return 1;
}

public mixed checkempty()
{
    if (!owner)
    {
        return 0;
    }
    object player=find_player(owner);
    if (!player || !interactive(player))
    {
        return "This is too heavy to pick up, as if something heavy "+
            "is in it.\n";
    }
    return 0;
}


public string query_owner()
{
    return owner;
}

public string get_desc_for_cost(int cost)
{
    switch (cost)
    {
        case 0..50: return "plain";
        case 51..1000: return "simple";
        case 1001..10000: return "elaborate";
        case 10001..50000: return "impressive";
        case 50001..100000: return "ornate";
        case 100001..1000000: return "extravagent";
        default: return "priceless";
    }
}

public void set_lining(string s)
{
    remove_item(lining);
    lining=s;
    add_item(({ "lining","inside", lining }), 
        "A selection of "+lining_color+" "+lining+" has been made to "+
        "line the inside of this coffin.\n");
}

public string query_lining()
{
    return lining;
}

public void set_lining_color(string s)
{
    lining_color=s;
}

public string query_lining_color()
{
    return lining_color;
}

public void set_material(string s)
{
    remove_item(material);
    material=s;
    add_item(({ "construction", s }), 
        "The coffin is made of the finest " + s + ".\n");
    add_adj(material);
}

public void set_cost_desc(string s)
{
    cost_desc=s;
}

public void set_carving(string s)
{
    carving=s;
    add_item(({ "carving", "carvings", "depictions", }), 
    "There are carvings all along the top and sides of this coffin, "+
    "depicting "+carving+".\n");
}

public string query_carving()
{
    return carving;
}

public void set_material_cost(int i)
{
    material_cost=i;
    set_cost_desc(get_desc_for_cost(material_cost));
    add_prop(OBJ_I_VALUE,i);
}

public int query_material_cost()
{
    return material_cost;
}


public void set_destroyed(string who)
{
    destroyer=who;
    if (strlen(destroyer))
    {
        remove_prop(CONT_I_LIGHT);
        remove_prop(OBJ_M_NO_GET);
        remove_prop(CONT_I_CLOSED);
        remove_name("coffin");
        set_name("ashes");
        set_adj(({ "pile", "large" }));
        on_fire=0;
        if (!owner)
        {
            return;
        }
        object player=find_player(owner);
        if (player && interactive(player) && 
            player->query_default_start_location()==MASTER_OB(TO))
        {
            //They were not in the coffin at time of destruction
            player->set_default_start_location(player->query_def_start());
        }
        if (player && environment(player)==TO)
        {
            surprise_vampire(player,destroyer);
        }
    }
}

public string query_destroyed()
{
    return destroyer;
}

public int
item_id(string str)
{
    if (query_destroyed())
    {
        return 0;
    }
    if (str==lining && strlen(lining) && (ENV(TO)==TP || 
    !TO->query_prop(CONT_I_CLOSED)))
    {
        return 1;
    }

    switch (str)
    {
        case "carving":
        case "carvings":
            if (ENV(TO)==ENV(TP) && strlen(carving))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        case "lining":
        case "inside":
            if (strlen(lining) && (ENV(TO)==TP || 
                !TO->query_prop(CONT_I_CLOSED)))
            {
                return 1;
            }
            else
            {
                return 0;
            }
    }
    return ::item_id(str);
}

public int query_lit(int type)
{
    return on_fire;
}


public int extinguish_me()
{
    if (on_fire)
    {
        remove_alarm(on_fire);
        on_fire=0;
        remove_prop(CONT_I_LIGHT);
        return 1;
    }
    return 0;
}

static int
coffin_enter(object who)
{
    int ret;
  
    if (strlen(query_destroyed()))
    {
        write("This coffin is destroyed and cannot be used.\n");
        return 0;
    }

    if (on_fire)
    {
        write("This coffin is on fire!\n");
        return 0;
    }


    if (!present(who, environment()))
    {
        write("Your coffin must be on the ground to enter.\n");
        return 0;
    }
    if (query_prop(CONT_I_CLOSED))
    {
        write("You must open your coffin to enter it.\n");
    }
    ret =  who->move_living("M", TO, 1, 1);
    return !ret;
}


public void load_coffin(mixed who)
{
    set_lining_color(COFFIN_MANAGER->query_lining_color(who));
    set_lining(COFFIN_MANAGER->query_lining(who));
    set_material(COFFIN_MANAGER->query_material(who));
    set_material_cost(COFFIN_MANAGER->query_material_cost(who));
    set_carving(COFFIN_MANAGER->query_carving(who));
    set_destroyed(COFFIN_MANAGER->query_destroyed(who));
    set_owner(COFFIN_MANAGER->get_name(who));
    if (strlen(material))
    {
        add_adj(material);
    }
    if (strlen(cost_desc))
    {
        add_adj(cost_desc);
    }
    add_adj("large");
}

public void save_coffin()
{
    if (!strlen(owner))
    {
        return;
    }
    COFFIN_MANAGER->set_lining(owner,lining);
    COFFIN_MANAGER->set_lining_color(owner,lining_color);
    COFFIN_MANAGER->set_material(owner,material);
    COFFIN_MANAGER->set_material_cost(owner,material_cost);
    COFFIN_MANAGER->set_carving(owner,carving);
    COFFIN_MANAGER->set_location(owner,MASTER_OB(ENV(TO)));
    COFFIN_MANAGER->set_destroyed(owner,0);
}

int
enter(string str)
{
    object env;
    string enter_msg;
  
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[into] [my] / [the] / [" +
        TP->query_real_name() + "'s] 'coffin'"))
    {
    	notify_fail("Enter what?\n");
    	return 0;
    }

    setuid();
    seteuid(getuid());

    env = environment(TP);
    if (coffin_enter(TP))
    {
        setuid();
        seteuid(getuid());
        enter_msg = COFFIN_MANAGER->query_enter_msg(TP);
 
        write("You lie down inside your coffin and close the lid " +
	    "above you.\n");
    
        if (strlen(enter_msg))
	    {
            tell_room(env, enter_msg + "\n");
	    }
        else
	    {
            tell_room(env, ({ TP->query_name()  + " lies down in " +
                POSS(TP) + " coffin, closing the lid securely.\n",
	    	"The "+TP->query_nonmet_name()  + " lies down in " + 
                POSS(TP) + " coffin, closing the lid securely.\n",
                "" }));
	    }
	    add_prop(CONT_I_CLOSED,closed_from_outside);
    }
    return 1;
}

/*
 * Function name: real_short
 * Description  : Returns the short without the addition of open/close
 * Arguments    : for_obj - who wants to know the short
 * Returns      : The short description
 */
public varargs string
real_short(object for_obj)
{
    return short(for_obj);
}

public string short(object for_obj)
{
    if (!for_obj)
    {
        for_obj=TP;
    }
    if (strlen(query_destroyed()))
    {
        return "large pile of ashes";
    }
    string burning=(on_fire ? "burning " : "");
    if (for_obj && ENV(for_obj)==TO)
    {
        return "Inside a "+burning+"coffin";
    }
    return 
        burning+
        (strlen(cost_desc) ? cost_desc+ " " : "") +
        (strlen(material) ? material + " " : "") +
        "coffin";
}

public mixed long(string str,object for_obj)
{
    if (strlen(str))
    {
        if (item_id(str))
        {
            return ::long(str,for_obj);
        }
        return 1;
    }
    if (strlen(query_destroyed()))
    {
        return "This is a large pile of ashes that was once a coffin.\n";
    }
    if (!for_obj)
    {
        for_obj=TP;
    }
    
    string desc;
    
    string inside="";
    if (strlen(lining) && strlen(lining_color))
    {
        if (for_obj && environment(for_obj)==TO)
        {
            inside=" The inside of the coffin is covered with "+
            lining+ ". The "+lining_color+" fabric enshrouds you "+
            "in opulence while providing comfort as you rest inside.";
        }
        else
        {
            inside=" The inside of the coffin is covered with "+
            lining+ ". The "+lining_color+" fabric enshrouds the "+
            "owner in opulence while providing comfort for "+
            "whatever lays inside.";
        }
    }
    else
    {
        inside=" The inside of the coffin lacks any lining, leaving "+
        "the bare "+material+" exposed.";

    }
    string burning="";
    if (on_fire)
    {
        burning+=" The coffin is on fire!";
    }
    else
    if (burn_level>0)
    {
        burning+=" The coffin has some burn marks, and is doused in oil.";
    }
    if (!strlen(lining) || !strlen(lining_color))
    {
        if (MASTER_OB(ENV(TO))==ROOM_DIR+"workshop" 
            && (IS_VAMP(for_obj) || IS_WIZ(for_obj)))
        {
            burning+="\nYou can line the coffin here with materials"+
            " of any color, if you bring the materials here.\n";
        }
    }
        
    if (for_obj && environment(for_obj)==TO)
    {
        desc="A large and well appointed coffin.";
        desc+=inside;
        desc+=" A sturdy lock on the inside keeps the coffin from "+
        "being opened while you rest.\n";
        desc+=burning;
        return desc;
    }
    desc="This is "+LANG_ADDART(cost_desc)+" large coffin made of "+
        material+".";
    
    if (!query_prop(CONT_I_CLOSED))
    {
        desc+=inside;
    }
    if (strlen(carving))
    {
        desc+=" Carved into the top and sides are depictions of "+
        carving+".";
    }
    else
    {
        desc+=" The solid "+material+" construction looks quite sturdy.";
        if (MASTER_OB(ENV(TO))==ROOM_DIR+"workshop" 
            && (IS_VAMP(for_obj) || IS_WIZ(for_obj)))
        {
            desc+="\n\nYou notice tools here to let you carve a design "+
            "into this coffin.\n";
        }
    }
    desc+=burning;
    desc+="\n";
    return desc;
    
}


int
prevent_enter(object ob)
{
    if (!IS_CLONE)
    {
        return 0;
    }
    if (query_destroyed())
    {
        return 0;
    }
    if (!living(ob))
    {
        return 0;
    }

    if (!interactive(ob))
    {
        write(ob->query_The_name()+" cannot go there.\n");
        return 1;
    }
    
    if (!strlen(owner) && !COFFIN_MANAGER->query_destroyed(ob))
    {
        object * 
        mycoffins=filter(object_clones(
            find_object(MASTER_OB(TO))),
            &operator (==) (ob->query_real_name(),) @ &->query_owner());
        if (sizeof(mycoffins)>0)
        {
            write("You already have another coffin.\n");
            return 1;
        }
    }
    
    if (strlen(owner) && (ob->query_real_name() != owner))
    {
        write("This is not your coffin.\n");
        return 1;
    }

    if (!owner)
    {
        object * 
        mycoffins=filter(object_clones(
            find_object(MASTER_OB(TO))),
            &operator (==) (ob->query_real_name(),) 
            @ &->query_owner());
        mycoffins->remove_ashes();
        set_owner(ob->query_real_name());
    }
    if (environment(TO)->query_prop(VAMP_CAN_START_HERE))
    {
        write("You may start here in your coffin, if you wish.\n");
        save_coffin();
    }
    return 0;
}


// Get out of the coffin once we are in it
int
rise(string str)
{
    notify_fail("Rise from the coffin?\n");
        
    if (strlen(str) &&
	    !parse_command(str, ({ }), "'from' [my] / [the] 'coffin'"))
    {
	    return 0;
    }
    
    object env=ENV(TO);
    while (env && !env->query_prop(ROOM_I_IS))
    {
        env=ENV(env);
    }
    
    if (!env)
    {
        write("The coffin is not stable on the ground, and the lid "+
            "cannot be opened.\n");
        return 1;
    }
    
    remove_prop(CONT_I_CLOSED);
        
    string rise_msg;
  
    if (TP->query_real_name() == owner)
    {
        rise_msg = COFFIN_MANAGER->query_rise_msg(TP);
    }
  
    if (strlen(rise_msg))
    {
        tell_room(env, rise_msg + "\n");
    }
    else
    {
        tell_room(env, QCTNAME(TP) +
            " rises from " +
            ((TP->query_real_name() == owner) ? POSS(TP) : "a") +
            " coffin.\n");
    }
  
    TP->move_living("M", env, 1);
  
    return 1;
}

void
gs_hook_start_meditate() { }
 
void
gs_hook_rise() { }

int
gs_hook_catch_error(string str)
{
    if (IS_WIZ(TP))
    {
        return 0;
    }
  
    write("You can't seem to focus your mind on that.\n");
    return 1;
}

int
gs_catch_all(string str)
{
    string action = query_verb();
  
    if (action == "rise")
    {
    
    	TP->remove_prop(LIVE_S_EXTRA_SHORT);
    	gs_rise();
    	return rise(str);
    }
  
    if (!TP->query_prop(LIVE_I_MEDITATES))
    {
        return 0;
    }
     
    action = query_verb();
  
    switch (action)
    {
#if 0
    	case "estimate":
	    return assess(str);
#endif
    	case "meditate":
	    return gs_meditate("");
    	case "set":
	    set_prefs();
	    return 1;
        case "get":
        case "drop":
    	case "stats":
    	case "quit":
    	case "commune":
    	case "reply":
    	case "bug":
    	case "typo":
    	case "idea":
    	case "praise":
    	case "sysbug":
    	case "vthirst":
    	case "vscry":
    	case "vth":
    	case "look":
    	case "examine":
        case "l":
        case "exa":
        case "vamps":
        case "start":
	    return 0;
    	default:
	    return gs_hook_catch_error(str);
    }
}

public int
start(string str)
{
    if (!IS_VAMP(TP) || TP->is_emerald_vampire())
	return 0;

    if (!environment(TO)->query_prop(VAMP_CAN_START_HERE))
    {
        write("Your coffin cannot start in this location.\n");
        return 1;
    }

    TP->set_default_start_location(MASTER_OB(TO));
    write("You will now awake from within your coffin.\n");
    return 1;
}

public void remove_ashes()
{
    WATCHERS(TO)->catch_msg("The pile of ashes blows away and is "+
    "gone.\n");
    remove_object();
}


public void burn_it()
{
    burn_level++;
    if (burn_level>10)
    {
        WATCHERS(TO)->catch_msg(capitalize(LANG_THESHORT(TO))+ 
        " falls apart into a pile of ash.\n");
        set_destroyed(arsonist);
        if (strlen(owner))
        {
            COFFIN_MANAGER->set_destroyed(owner,arsonist);
        }
    }
    else
    {
        switch (random(4))
        {
            case 0:
            WATCHERS(TO)->catch_msg("Smoke arises from "+
            LANG_THESHORT(TO) + ".\n");
            break;
            case 1:
            WATCHERS(TO)->catch_msg("Fierce flames dance across "+
            LANG_THESHORT(TO) + ".\n");
            break;
            case 2:
            WATCHERS(TO)->catch_msg("Shadows flicker along the walls as "+
            LANG_THESHORT(TO) + " crackles.\n");
            break;
            default:
            WATCHERS(TO)->catch_msg("Large flames leap out of "+
            LANG_THESHORT(TO) + ".\n");
        }
        object * inside=filter(all_inventory(TO),&living());
        if (sizeof(inside))
        {
            foreach(object ob : inside)   
            {
                ob->heal_hp(-ob->query_max_hp()/20);
                ob->catch_msg("You are burning with the coffin!\n");
            }
        }
        on_fire=set_alarm(3.0,0.0,burn_it);
    }
}

public int burn(string str)
{
    notify_fail("Burn what?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    if (on_fire)
    {
        notify_fail("The coffin is already on fire.\n");
        return 0;
    }
    if (query_destroyed())
    {
        notify_fail("This coffin is already a pile of ashes.\n");
        return 0;
    }
    if (ENV(TO)!=ENV(TP))
    {
        notify_fail("You cannot burn a coffin while you carry it.\n");
        return 0;
    }
    object coffin;
    if (!parse_command(str,all_inventory(ENV(TP)),"%o",coffin) ||
        coffin!=TO)
    {
        return 0;
    }
    int oil=0;
    object * 
    oil_flasks = filter(all_inventory(TP),
        &->id("_gondorian_flask_with_oil_"));
    foreach (object flask : oil_flasks)
    {
        oil+=flask->query_amount();
    }
    if (oil<15000 && burn_level==0)
    {
        write("You do not have enough oil to burn the coffin.\n");
        return 1;
    }
    object * lights=filter(all_inventory(TP),
        &->query_prop(OBJ_I_HAS_FIRE));
    if (!sizeof(lights))
    {
        write("You do not have any fire with which to burn the coffin.\n");
        return 1;
    }
    if (!burn_level)
    {
        oil=15000;
        foreach (object flask : oil_flasks)
        {
            int to_remove=min(flask->query_amount(),oil);
            if (to_remove>0)
            {
                flask->remove_oil(to_remove);
                oil-=to_remove;
            }
        }
        write("You pour oil all over "+LANG_THESHORT(TO)+", dousing it "+
            "with the flammable substance. As the oil drips down along "+
            "the coffin, you touch your "+lights[0]->short()+" to it, "+
            "setting it ablaze.\n");

        all(" pours oil all over "+LANG_THESHORT(TO)+", dousing it with "+
            "the flammable substance. As the oil drips down along the "+
            "coffin, "+ PRO(TP)+" touches " + POSS(TP)+" "+
            lights[0]->short() + " to it, setting it ablaze.\n");
    }
    else
    {
        write("You touch your "+lights[0]->short()+" to "+
            LANG_THESHORT(TO)+", setting it ablaze.\n");
        all(" touches "+POSS(TP)+" "+ lights[0]->short() +
            " to "+LANG_THESHORT(TO)+", setting it ablaze.\n");
    }
    
    arsonist=TP->query_real_name();
    write_file(LOG_DIR+"coffins",capitalize(arsonist)+" lit "+
    (strlen(owner) ? owner +"'s" : "an unclaimed") + " coffin on fire.\n");
    add_prop(OBJ_M_NO_GET,"You cannot pick up a burning coffin.\n");
    add_prop(CONT_I_LIGHT,3);
    
    on_fire=set_alarm(3.0,0.0,burn_it);
    return 1;
}


void
init()
{
    ::init();

    if (ENV(TP)==TO)
    {
        init_guild_support();
        add_action(rise,"rise");
        add_action(rise,"out");
        add_action(rise,"leave");
        add_action(start,"start");
        return;
    }

    add_action(burn,"burn");

    if (!COFFIN_OWNER(TP) && !IS_WIZ(TP) && strlen(owner))
    {  
        return;
    }

    add_action(enter, "enter");
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    if (ENV(for_obj)!=TO && ENV(for_obj)!=ENV(TO))
    {
        return;
    }
    if (strlen(query_destroyed()))
    {
        ::describe_contents(for_obj,obarr);
        return;
    }

    for_obj->catch_tell(show_sublocs(for_obj));

    string prefix="";
    if (environment(for_obj)==TO)
    {
        obarr-=({ for_obj });
        prefix="Besides you, ";
    }
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell(capitalize(prefix+ "the coffin contains " + 
            COMPOSITE_DEAD(obarr) + ".\n"));
    }
    else
    {
        for_obj->catch_tell("  " + capitalize(prefix + "the coffin is "+
        "empty.\n"));
    }
}

public string exits_description()
{
    return "";
}

void
move_def_start(object ob)
{
    mixed start;

    if (!strlen(start = ob->query_default_start_location()) &&
        !strlen(start = ob->query_def_start()))
    {
        start=environment(TO);
    }

    ob->move(start);
}

void
remove_object()
{
    map(deep_inventory(), move_def_start);
    ::remove_object();
}    

public int query_coffin()
{
    return 1;
}

public void surprise_vampire(object vampire,string destroyer)
{
    vampire->move_living("M",ROOM_DIR+"crypt",1,1);
    if (vampire->query_real_name()==destroyer)
    {
        vampire->catch_msg("You wake up at the feet of the Eldest, "+
        "as you had destroyed your coffin.\n");
        vampire->set_default_start_location(vampire->query_def_start());
        return;
    }
    vampire->heal_hp(-vampire->query_hp()*9/10);
    int blood=vampire->query_blood();
    if (blood>0)
    {
        vampire->add_blood(-blood/2);
    }
    vampire->catch_msg("You were burned alive in your coffin! The "+
        "intense pain of the flames across your skin, consuming your "+
        "flesh, is all too vivid, and you find yourself at the brink "+
        "of death. Your soul feels barely attached to this world, "+
        "thoughts of leaving this existance linger in your mind.\n\n\n");
    int unprotected=OCC_MANAGER->query_unprotected(vampire);
    if (!unprotected)
    {
        vampire->catch_msg("A thought passes through your mind: Come "+
            "back to us, you are immortal and you are blessed.\n"+
            "The pain subsides somewhat, and your soul remains "+
            "attached to your body - though you still have much to "+
            "recover.\n");
    }
    else
    {
        vampire->remove_vampire();
    }
}

public void enter_inv(object ob, object from)
{
    if (!IS_CLONE)
    {
        object * 
        mycoffins=filter(object_clones(TO),
            &operator (==) (ob->query_real_name(),) @ &->query_owner());
        if (sizeof(mycoffins)>0)
        {
            ob->move(mycoffins[0],1);
            return;
        }
        string location=COFFIN_MANAGER->query_location(ob);
        if (!location || !strlen(location))
        {
            ob->move_living("M",ROOM_DIR+"crypt",1,1);
            ob->catch_msg("You expect to wake up in your coffin, "+
                "but find yourself instead at the feet of the "+
                "Eldest.\n");
            COFFIN_MANAGER->delete_data(ob->query_real_name());
            return;
        }
        LOAD_ERR(location);
        mycoffins=filter(object_clones(TO),
            &operator (==) (ob->query_real_name(),) 
            @ &->query_owner());
        if (sizeof(mycoffins)>0)
        {
            ob->move(mycoffins[0],1);
            return;
        }
        ob->move_living("M",ROOM_DIR+"crypt",1,1);
        ob->catch_msg("You expect to wake up in your coffin, "+
            "but find yourself instead at the feet of the "+
            "Eldest.\n");
        COFFIN_MANAGER->delete_data(ob->query_real_name());
        return;
    }
    if (strlen(query_destroyed()))
    {
        set_alarm(0.0,0.0,&surprise_vampire(ob,query_destroyed()));
    }
    ::enter_inv(ob,from);
}

public void leave_inv(object ob, object to)
{
    if (!IS_CLONE)
    {
        return;
    }
    ::leave_inv(ob,to);
}

public int
close(string str)
{
    if (query_destroyed())
    {
        write("There is no lid to open.\n");
        return 2;
    }
    return 0;
}


public int
open(string str)
{
    if (query_destroyed())
    {
        return 2;
    }
    if (!owner || TP->query_real_name()==owner)
    {
        return 0;
    }
    write("The coffin is somehow locked, but you can see no keyhole.\n");
    return 2;
}

