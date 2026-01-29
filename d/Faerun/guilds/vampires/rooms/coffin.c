/* coffin.c created by Novo 
 *
 * This is the standard resting place for a vampire.
 *
 * Modified and used with permission from Novo,
 * Nerull 2021.
 *
 * Changes:
 * 2021-10-17 - Cotillion
 * - Fixed a runtime in closed_from_outside
 */

#pragma save_binary

inherit "/std/receptacle";
inherit "/lib/guild_support";
inherit "/lib/commands";
//inherit "/lib/skill_raise";

#include "../guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <mail.h>
#include <std.h>

#define OBJ_I_FLOAT         "_obj_i_float"
#define COFFIN_OWNER(x)     (owner==x->query_real_name())
#define VAMP_CAN_START_HERE "_vamp_can_start_here"
#define LOG_DIR             "/d/Faerun/guilds/vampires/master/log/general_logs/"
#define TO this_object()
#define TP this_player()

#define ENV(obj)            environment(obj)
#define VAMPIRE_POWERS_UNLOCK_OB  "/d/Faerun/guilds/vampires/obj/vampire_powers_unlock_ob"
#define SIGIL_WARNING       "_vamp_sigil_warning"
#define IS_WIZ(x) (interactive(x) && \
    SECURITY->query_wiz_rank(x->query_real_name()))
    
//void set_up_skills();

int on_fire=0;
int burn_level=0;
string arsonist;
string destroyer;

string owner;
string lining;
string lining_color;
string material;
int material_cost;

int sigil;
int owner_avg;

string cost_desc;
string carving;

public void set_material_cost(int i);
public void set_material(string m);
public void surprise_vampire(object vampire,string destroyer);
public void closed_from_outside();
public void checkempty();
public void checkvampire();

public string get_desc_for_cost(int cost);
public int query_material_cost();

void
update_position()
{
    COFFIN_MANAGER->set_location(owner,MASTER_OB(environment(TO)));
    
    if (this_object()->query_prop(CONT_I_CLOSED) == 0)
    {
        this_object()->add_prop(CONT_I_CLOSED, 1);
        
        WATCHERS(TO)->catch_msg("The "+short()+" magically closes itself.\n");
    }
}

void
create_receptacle()
{
    set_name( ({ "coffin", "vamp_coffin" }) );
    
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(CONT_I_CLOSED,closed_from_outside);
    add_prop(OBJ_M_NO_GET,checkvampire);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(CONT_I_VOLUME,50000);
    
    //add_prop(OBJ_I_FLOAT, 1);

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
    
//    create_skill_raise();
//    set_up_skills();
    
    set_material_cost(0);
    set_material(material);
    set_cf(TO);

    setuid();
    seteuid(getuid());
    
    set_alarm(0.5, 120.0, &update_position());
}


/*void
set_up_skills()
{
    string to;
    
    // Layman skills
    to = "x";
    sk_add_train(SS_APPR_MON,         ({ to, to }), 0, 0, 60);
    
    to = "x";
    sk_add_train(SS_TRACKING,         ({ to, to }), 0, 0, 60);
    
    to = "x";
    sk_add_train(SS_LOC_SENSE,        ({ to, to }), 0, 0, 60);
       
    to = "x";
    sk_add_train(SS_ELEMENT_AIR,      ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_ELEMENT_WATER,    ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_ELEMENT_DEATH,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_FORM_ABJURATION,  ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_CONJURATION, ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_FORM_ILLUSION,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_SPELLCRAFT,       ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_HERBALISM,        ({ to, to }), 0, 0, 60);
    
    
    // Racial skills
    to = "x";
    sk_add_train(SS_OPEN_LOCK,   ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_APPR_VAL,    ({ to, to }), 0, 0, 50);
       
    to = "x";
    sk_add_train(SS_LANGUAGE,    ({ to, to }), 0, 0, 50);
    
    to = "x";
    sk_add_train(SS_CLIMB,       ({ to, to }), 0, 0, 60);
    
    sk_add_train(SS_ANATOMY, "in the knowledge of Anatomy",
    "anatomy",100,100,SS_DEX,100);
}*/


int
do_blockskillraise()
{
    write("What?\n");
    
    return 1;
}


public void remove_ashes()
{
    WATCHERS(TO)->catch_msg("The pile of ashes fades away.\n");
    remove_object();
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
    
    if (this_player() && environment(TP) == TO)
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
        return "The coffin is too bulky for you to pick up.\n";
    }
    object player=find_player(owner);
    if (!player || !interactive(player))
    {
        return "The coffin is too bulky for you to pick up.\n";
    }
    return 0;
}


public string get_desc_for_cost(int cost)
{
    switch (cost)
    {
        case 0..50: return "plain";
        case 51..80: return "simple";
        case 81..99: return "elaborate";
    }
}


/*
 * Function name: empty_out()
 * Description  : Moves all objects to the environment
 */
int
empty_out(object ob)
{
    if (ob->move(environment(this_object())))
        return 0;
    else
        return 1;
}


public mixed checkvampire()
{
    object coffin_owner_token;
    
    if (!owner)
    {
        return "The coffin is too bulky for you to pick up.\n";
    }
    
    object player=find_player(owner);
    
    if (!player || !interactive(player))
    {
        return "This is too heavy to pick up, as if something heavy "+
            "is in it.\n";
    }
    
    if (strlen(owner) && (TP->query_real_name() != owner))
    {
         return "The coffin is too bulky for you to pick up.\n";
    }
    
    if (sizeof(all_inventory(this_object())))
    {
        return "The coffin is not empty. Clear it first.\n";
    }
    
    this_player()->catch_tell("You pick up your own coffin.\nWhen "
    +"you pick it up, the content and dust spills on the ground.\n");
        
    tell_room(environment, ({ TP->query_name()  + " picks up " +
                POSS(TP) + " coffin.\n",
            "The "+TP->query_nonmet_name()  + " picks up " + 
                POSS(TP) + " coffin.\n",
                "" }));
                 
    if (material == "wood")
    {
        string firstdesc;
        
        int costa = query_material_cost();
        
        switch (costa)
        {
            case 0..50: 
            firstdesc = "plain";
            break;
            case 51..80: 
            firstdesc = "simple";
            break;
            case 81..99: 
            firstdesc = "elaborate";     
            break;            
        }
        
        if (firstdesc == "plain")
        {
            object coffin_owner_token1 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_1_1");
            
            coffin_owner_token1->move(this_player(), 1);
        }
        
        if (firstdesc == "simple")
        {
            object coffin_owner_token2 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_1_2");
            
            coffin_owner_token2->move(this_player(), 1);
        }
        
        if (firstdesc == "elaborate")
        {
            object coffin_owner_token3 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_1_3");
            
            coffin_owner_token3->move(this_player(), 1);
        }
    }
    
    if (material == "stone")
    {
        string firstdesc;
        
        int costa = query_material_cost();
        
        switch (costa)
        {
            case 0..50: 
            firstdesc = "plain";
            break;
            case 51..80: 
            firstdesc = "simple";
            break;
            case 81..99: 
            firstdesc = "elaborate";     
            break;            
        }
        
        if (firstdesc == "plain")
        {
            object coffin_owner_token4 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_2_1");
            
            coffin_owner_token4->move(this_player(), 1);
        }
        
        if (firstdesc == "simple")
        {
            object coffin_owner_token5 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_2_2");
            
            coffin_owner_token5->move(this_player(), 1);
        }
        
        if (firstdesc == "elaborate")
        {
            object coffin_owner_token6 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_2_3");
            
            coffin_owner_token6->move(this_player(), 1);
        }
    }
    
    if (material == "steel")
    {
        string firstdesc;
        
        int costa = query_material_cost();
        
        switch (costa)
        {
            case 0..50: 
            firstdesc = "plain";
            break;
            case 51..80: 
            firstdesc = "simple";
            break;
            case 81..99: 
            firstdesc = "elaborate";     
            break;            
        }
        
        if (firstdesc == "plain")
        {
            object coffin_owner_token7 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_3_1");
            
            coffin_owner_token7->move(this_player(), 1);
        }
        
        if (firstdesc == "simple")
        {
            object coffin_owner_token8 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_3_2");
            
            coffin_owner_token8->move(this_player(), 1);
        }
        
        if (firstdesc == "elaborate")
        {
            object coffin_owner_token9 = clone_object(VAMPIRES_GUILD_DIR 
            + "obj/coffin_owner_token_3_3");
            
            coffin_owner_token9->move(this_player(), 1);
        }
    }
    
    map(all_inventory(this_object()), empty_out);
        
    COFFIN_MANAGER->remove_coffin(this_player()->query_real_name());
    
    object powertoken;
        
    while (powertoken = present("_vampire_powers_unlock_ob", 
    this_player()))
    {
        this_player()->catch_tell("You feel a drain in power. You will not "
        +"be able to use most gifts as long as no coffin is firmly placed on "
        +"the ground, connecting to the realm.\n");

        powertoken->remove_object();
    }
    
    // If the vampire is on the aging list for some reason, we end it here.
    if (VAMPIRES_MASTER->is_aging_check(this_player()->query_real_name()))
    {
        powertoken->remove_object();
        
        remove_object();
        
        return 0;
    }
    
    // Add vampires to list of noaging vampires.
    VAMPIRES_MASTER->add_aging_check(this_player()->query_real_name());
    
    remove_object();
    
    return 0;
}


public string query_owner()
{
    return owner;
}


public string query_mat()
{
    return material;
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


public void set_sigil(int i)
{
    sigil=i;
}


public int query_sigil()
{
    return sigil;
}


public void set_owner_avg(int i)
{
    owner_avg=i;
}


public int query_owner_avg()
{
    return owner_avg;
}


public void set_destroyed(string who)
{
    destroyer=who;
    
    if (strlen(destroyer))
    {
        remove_prop(CONT_I_LIGHT);
        remove_prop(CONT_I_CLOSED);
        add_name("ashes");
        set_adj(({ "pile", "large" }));
        
        set_short("large pile of ashes");
        
        
        on_fire=0;
        
        if (!owner)
        {
            return;
        }
        
        object player=find_player(owner);
        
        // If player is online, but not in coffin
        if (player && environment(player)!= TO)
        {
            player->catch_tell("You sense that your coffin "
            +"has been destroyed!\nYou feel a drain in your "
            +"power!\n");
            
            VAMPIRES_MASTER->add_aging_check(player->query_real_name());
            
            COFFIN_MANAGER->remove_coffin(player->query_real_name());
            
            object powertoken1;
        
            while (powertoken1 = present("_vampire_powers_unlock_ob", 
            player))
            {
                powertoken1->remove_object();
            }
            
            remove_ashes();
            
            TO->remove_object();
            
            return;
        }
        
        // If player is online, but inside the coffin
        if (player && environment(player)==TO)
        {
            surprise_vampire(player,destroyer);
        }
    }
}


int query_no_pick()
{
    return 1;
}


public int dispatch_coffin(string str)
{
    if (str == "coffin")
    {
        if (VAMPIRES_MASTER->is_lay_vampires(this_player()->query_name()) == 0)
        {
            return 0;
        }
            
        if (!owner)
        {
            this_player()->catch_tell("This is not your coffin!\n");
            return 1;
        }
        
        if (environment(this_player()) == this_object())
        {
            this_player()->catch_tell("You can't dispatch your "
            +"coffin while being in it!\n");
            return 1;
        }
        
        this_player()->catch_tell("You dispatch your own coffin!\nYou "
        +"feel a drain in your power!\n");
        
        VAMPIRES_MASTER->add_aging_check(this_player()->query_real_name());
        
        object powertok;
        
        while (powertok = present("_vampire_powers_unlock_ob", 
        this_player()))
        {
            powertok->remove_object();
        }
        
        COFFIN_MANAGER->remove_coffin(this_player()->query_real_name());
        
        remove_object();
        
        return 1;
    }
    
    this_player()->catch_tell("Dispatch what?\n");
    
    return 1;
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
    
    if (str==lining && strlen(lining) && (environment(TO)==TP || 
    !TO->query_prop(CONT_I_CLOSED)))
    {
        return 1;
    }

    switch (str)
    {
        case "carving":
        case "carvings":
            if (environment(TO)==environment(TP) && strlen(carving))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        case "lining":
        case "inside":
            if (strlen(lining) && (environment(TO)==TP || 
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
  
    if (query_prop(CONT_I_CLOSED))
    {
        write("You must open your coffin to enter it.\n");
    }
    
    object token;
    
    if (!IS_VAMP_MEMBER(who))
    {
        if (!IS_SPAWN_MEMBER(who))
        {
            write("Ehm...no. Coffins belong to corpses.\n");
            return 1;
        }
    }
    
    if (query_destroyed() != 0)
    {
        write("This coffin is destroyed, reduced to ashes!\n");
        
        return 1;
    }
    
    ret =  who->move_living("M", TO, 1, 1);
    
    set_owner_avg(who->query_average());  
    
    return !ret;
}


public void load_coffin(mixed who)
{
    set_lining_color(COFFIN_MANAGER->query_lining_color(who));
    set_lining(COFFIN_MANAGER->query_lining(who));
    set_material(COFFIN_MANAGER->query_material(who));
    set_material_cost(COFFIN_MANAGER->query_material_cost(who)); 
    
    set_sigil(COFFIN_MANAGER->query_sigil(who));
    set_owner_avg(COFFIN_MANAGER->query_owner_avg(who));    
    
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
    
    COFFIN_MANAGER->set_sigil(owner,sigil);
    COFFIN_MANAGER->set_owner_avg(owner,owner_avg);
    
    COFFIN_MANAGER->set_carving(owner,carving);

    COFFIN_MANAGER->set_location(owner,MASTER_OB(environment(TO)));
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
    
    if (!IS_VAMP_MEMBER(TP))
    {
        if (!IS_SPAWN_MEMBER(TP))
        {
            notify_fail("Ehm...no. Coffins belong to corpses.\n");
            return 0;
        }
    }
    
    object token;
    
    if (query_destroyed() != 0)
    {
        write("This coffin is destroyed, reduced to ashes!\n");
        
        return 1;
    }
    
    setuid();
    seteuid(getuid());

    env = environment(TP);
    
    if (coffin_enter(TP))
    {
        setuid();
        seteuid(getuid());
        
        object token;
    
        enter_msg = COFFIN_MANAGER->query_enter_msg(TP);
 
        write("You lie down inside your coffin and close the lid " +
        "above you.\n");
        
        TP->set_default_start_location(MASTER_OB(TO));
        write("You will now awake from within your coffin.\n");
        
       // int qavg = TP->query_average();
        
       // set_owner_avg = qavg;
        
        int qavg = TP->query_average();
        
        owner_avg = qavg;
            
        //COFFIN_MANAGER->set_owner_avg(TP,owner_avg);
        
        save_coffin();
        
        set_owner_avg(COFFIN_MANAGER->query_owner_avg(TP));    
    
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
    
    if (for_obj && environment(for_obj)==TO)
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
        if (MASTER_OB(environment(TO))==ROOM_DIR+"workshop" 
            && (IS_VAMP_MEMBER(for_obj) || IS_WIZ(for_obj)))
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
        /*if (MASTER_OB(ENV(TO))==ROOM_DIR+"workshop" 
            && (IS_VAMP_MEMBER(for_obj) || IS_WIZ(for_obj)))
        {
            desc+="\n\nYou notice tools here to let you carve a design "+
            "into this coffin.\n";
        }*/
        
        if (sigil == 1)
        {
            desc+="\nYou feel very uneasy near it, so you keep some distance.\n";
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
    
    save_coffin();

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
  
    if (!present("_vampire_powers_unlock_ob", TP))
    {
        clone_object(VAMPIRE_POWERS_UNLOCK_OB)->move(TP, 1);
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
        case "vampthirst":
        case "vampimmortality":
        case "vampsense":
        case "look":
        case "examine":
        case "l":
        case "exa":
        case "start":
        return 0;
        default:
        return gs_hook_catch_error(str);
    }
}


public int
start(string str)
{
    if (!IS_VAMP_MEMBER(TP) || !IS_SPAWN_MEMBER(TP))
    return 0;

    TP->set_default_start_location(MASTER_OB(TO));
    write("You will now awake from within your coffin.\n");
    return 1;
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
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" completed burning "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin to ashes.\n");
        
        VAMPIRES_MAPPINGS->set_thirst_gauge(owner, 1);  
        
        VAMPIRES_MASTER->add_aging_check(owner);
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


public void burn_it_underwater()
{
    burn_level++;
    
    if (burn_level>10)
    {
        WATCHERS(TO)->catch_msg(capitalize(LANG_THESHORT(TO))+ 
        " collapses into a pile of ash, that starts to drift "
        +"away in the water.\n");
        
        set_destroyed(arsonist);
        
        if (strlen(owner))
        {
            COFFIN_MANAGER->set_destroyed(owner,arsonist);
        }
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" completed burning "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin to ashes.\n");
        
        VAMPIRES_MAPPINGS->set_thirst_gauge(owner, 1);  
        
        VAMPIRES_MASTER->add_aging_check(owner);
    }
    else
    {
        switch (random(4))
        {
            case 0:
            WATCHERS(TO)->catch_msg("Water boils around "+
            LANG_THESHORT(TO) + " while it is burning.\n");
            break;
            case 1:
            WATCHERS(TO)->catch_msg("Fierce white flames ravages around "+
            LANG_THESHORT(TO) + " in the water.\n");
            break;
            case 2:
            WATCHERS(TO)->catch_msg("You are nearly blinded by the fierce "
            +"light of the flames when "+
            LANG_THESHORT(TO) + " burning.\n");
            break;
            default:
            WATCHERS(TO)->catch_msg("Large white flames leap out of "+
            LANG_THESHORT(TO) + ", boiling the surrounding water instantly.\n");
        }
        
        object * inside=filter(all_inventory(TO),&living());
        
        if (sizeof(inside))
        {
            foreach(object ob : inside)   
            {
                ob->heal_hp(-ob->query_max_hp()/20);
                ob->catch_msg("You are burning and boiling with the coffin!\n");
            }
        }
        
        on_fire=set_alarm(3.0,0.0,burn_it_underwater);
    }
}


public void burn_it_stone()
{
    burn_level++;
    
    if (burn_level>4)
    {
        WATCHERS(TO)->catch_msg(capitalize(LANG_THESHORT(TO))+ 
        " collapses into a pile of rubble, that fades away.\n");
        
        set_destroyed(arsonist);
        
        if (strlen(owner))
        {
            COFFIN_MANAGER->set_destroyed(owner,arsonist);
        }
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" completed burning "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin to rubble. used dragonfire.\n");
        
        VAMPIRES_MAPPINGS->set_thirst_gauge(owner, 1);  
        
        VAMPIRES_MASTER->add_aging_check(owner);
    }
    else
    {
        
        WATCHERS(TO)->catch_msg("white-hot dragonfire engulfs "+
        LANG_THESHORT(TO) + " while it is melting.\n");
            
        object * inside=filter(all_inventory(TO),&living());
        
        if (sizeof(inside))
        {
            foreach(object ob : inside)   
            {
                ob->heal_hp(-ob->query_max_hp()/20);
                ob->catch_msg("You are burning with the coffin!\n");
            }
        }
        
        on_fire=set_alarm(3.0,0.0,burn_it_stone);
    }
}



public int burn(string str)
{
    notify_fail("Burn what?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    if (COFFIN_OWNER(TP))
    {
        notify_fail("No, you don't want to burn "
        +"your own coffin. To rid yourself of your "
        +"coffin, use 'dispatch coffin' instead.\n");
        return 0;
    }
    
    int destructeeav2 = this_player()->query_average();
    
    string tp_sire;
    string coffowner;
    
    coffowner = this_object()->query_owner();
    tp_sire = this_player()->query_sire();
    
    arsonist=this_player()->query_real_name();
    
    
    // Children can't burn the coffins of their sires.
    if (tp_sire == coffowner)
    {
        notify_fail("You lack the self-discipline to approach "
           +"the "+this_object()->short()+" with such "
           +"intentions becaue the owner is your Sire.\n");
        
        write_file(LOG_DIR+"coffins",capitalize(arsonist)+" tried to lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin on fire, but could not (Sire).\n");
        
        return 0;    
    }
           
    // Only players with same or larger avg than the 
    // guild and (-10 avg) joining
    // requirement dares to burn a coffin.
    if (150 > destructeeav2)
    {
        notify_fail("You lack the self-discipline to approach "
           +"the "+this_object()->short()+" with such "
           +"intentions and feel repelled by the power"
           +"emanating from the "+this_object()->short()+".\n");
           
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" tried to lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin on fire, but didn't dare. "+destructeeav2+".\n");
        
        write_file(LOG_DIR+"coffins",extract(ctime(time()) +":"+capitalize(arsonist)+" tried to lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin on fire, but didn't dare "+destructeeav2+".\n"));

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
    
    // Protective ward in place.
    if (this_object()->query_sigil() == 1)
    {
        int ownerav = query_owner_avg();
        int destructeeav = this_player()->query_average();
        
        // The ward will bounce back players smaller than the vampire
        if (ownerav > destructeeav)
        {
            if (this_player()->query_prop(LIVE_I_UNDEAD) == 0)
            {
                notify_fail("As you approach the "+this_object()->short()+", you sense "
                +"a strong aura of death around it. You do not "
                +"dare to burn it as you believe its cursed by "
                +"somebody greater than your stature.\n");
                
                return 0;
            }
            
            notify_fail("You sense "
            +"a strong comfortable aura of death around the "+this_object()->short()+".\n");
        }
        
        if (this_player()->query_prop(LIVE_I_UNDEAD) == 0)
        {
            if (this_player()->query_prop(SIGIL_WARNING) == 0)
            {
                notify_fail("As you approach the "+this_object()->short()+", you sense "
                +"a strong aura of death around it. have a strong sense that "
                +"the "+this_object()->short()+" is protected by a powerful ward "
                +"that will claim your life. Are you sure you "
                +"wish to proceed anyway?\n");
                
                this_player()->add_prop(SIGIL_WARNING, 1);
                
                return 0;
            }
                   
            notify_fail("You daringly approach the "+this_object()->short()+" in order "
            +"to burn it! Suddenly, a strange glyph covering the "+this_object()->short()+" "
            +"begins to glow in an eerie green light, before it "
            +"explodes violently in a outward fasion!\nAll your vitality "
            +"and life are instantly sucked out of your being!\nThe "
            +"powerful enchantment encapsulating the "+this_object()->short()+" dissipates!\n");
            
            tell_room(environment(this_object())), 
            QCTNAME(this_player()) + " gasps in fear as a strange glyph on the "
            +this_object()->short()+" begins to glow violently in an eerie green "
            +"light, before it explodes in a outward fasion.\nThe powerful enchantment "
            +"encapsulating the "+this_object()->short()+" dissipates!\n", 
            this_player();       
            
            this_player()->remove_prop(SIGIL_WARNING);
            
            this_player()->set_hp(0);
            this_player()->do_die(this_object());
            
            sigil = 0;  
            save_coffin();
        
            return 0;
        }
        
        notify_fail("You approach the "+this_object()->short()+" in order "
        +"to burn it! Suddenly, a strange glyph covering the "+this_object()->short()+" "
        +"begins to glow in an eerie green colour, before it "
        +"explodes violently in a outward fasion!\nYou feel renewed and restored!\nThe "
        +"powerful enchantment encapsulating the "+this_object()->short()+" dissipates!\n");
        
        tell_room(environment(this_object())), 
        QCTNAME(this_player()) + " gasps in fear as a strange glyph on the "
        +this_object()->short()+" begins to glow violently in an eerie green "
        +"light, before it explodes in a outward fasion.\nThe powerful enchantment "
        +"encapsulating the "+this_object()->short()+" dissipates!\n", 
        this_player();       
        
        this_player()->set_hp(10000);
        
        sigil = 0;  
        save_coffin();
        
        return 0;
        
    }
       
    if (query_mat() == "stone")
    {
        object *dragonfire;
        
        dragonfire = filter(deep_inventory(this_player()),
        &operator(==)("_dragonfire_flask") @&->query_name());

        if (!sizeof(dragonfire))
        {
            notify_fail("The coffin is made of stone, and you currently possess no "
            +"means to burn or destroy stone.\n");
            return 0;
        }
              
        write("You smash the glowing fiery flask at " 
        +"the "+LANG_THESHORT(TO)+". Almost immediately its set fully "
        +"ablaze by a white-hot fire that only ancient dragons "
        +"can produce!\n");

        all(" smashes a glowing fiery flask at "+LANG_THESHORT(TO)+", which "
        +"immediately is set ablaze! White-hot flames that only ancient "
        +"dragons can produce engulfs it entirely!\n");
        
        dragonfire[0]->reduce_heap_size();
        
        arsonist=TP->query_real_name();
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " stone coffin on fire with dragonfire. "+destructeeav2+".\n");
    
        write_file(LOG_DIR+"coffins",capitalize(arsonist)+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " stone coffin on fire with dragonfire. "+destructeeav2+".\n");
        
        add_prop(OBJ_M_NO_GET,"You cannot pick up a burning coffin.\n");
        
        add_prop(CONT_I_LIGHT,3);
        
        on_fire=set_alarm(3.0,0.0,burn_it_stone);
        
        return 1;
    }
    
    
    if (query_mat() == "steel")
    {
        object *truefire;
        
        truefire = filter(deep_inventory(this_player()),
        &operator(==)("_ttttfire_flask") @&->query_name());

        if (!sizeof(truefire))
        {
            notify_fail("The coffin is made of stone, and you currently possess no "
            +"means to burn or destroy stone.\n");
            return 0;
        }
               
        write("You open the large rust-red flask and start spreading out "
        +"its content all over the "+LANG_THESHORT(TO)+". Strange as it may be, the "
        +"rust-red powder reacts with the water and ignites immediately. In "
        +"seconds, the coffin is "
        +"set ablaze under water, giving away a white flaring and violent fire!\n");

        all(" spreads a lot of rusty powder from a large rust-red "
        +"flask all over "+LANG_THESHORT(TO)+", which "
        +"immediately reacts with the water and ignites into a "
        +"white flaring and violent fire! In seconds, "
        +"the coffin is set ablaze, burning under water!\n");
        
        truefire[0]->reduce_heap_size();
        
        arsonist=TP->query_real_name();
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " steel coffin on fire with hellfire under water. "+destructeeav2+".\n");
    
        write_file(LOG_DIR+"coffins",capitalize(arsonist)+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " steel coffin on fire with hellfire under water. "+destructeeav2+".\n");
        
        add_prop(OBJ_M_NO_GET,"You cannot pick up a burning coffin.\n");
        
        add_prop(CONT_I_LIGHT,3);
        
       // on_fire=set_alarm(3.0,0.0,burn_it_steel);
        
        return 1;
    }
    
    
    // Water room. Cant burn a submerged coffin by normal means.
    if (ENV(TO)->query_prop(ROOM_I_TYPE) == 2)
    {
        object *truefire;
        
        truefire = filter(deep_inventory(this_player()),
        &operator(==)("_hellfire_flask") @&->query_name());

        if (!sizeof(truefire))
        {
            notify_fail("The coffin is submerged in "
            +"water, and burning it by normal means is not possible.\n");
            return 0;
        }
        
        write("You open the large rust-red flask and start spreading out "
        +"its content all over the "+LANG_THESHORT(TO)+". Strange as it may be, the "
        +"rust-red powder reacts with the water and ignites immediately. In "
        +"seconds, the coffin is "
        +"set ablaze under water, giving away a white flaring and violent fire!\n");

        all(" spreads a lot of rusty powder from a large rust-red "
        +"flask all over "+LANG_THESHORT(TO)+", which "
        +"immediately reacts with the water and ignites into a "
        +"white flaring and violent fire! In seconds, "
        +"the coffin is set ablaze, burning under water!\n");
        
        truefire[0]->reduce_heap_size();
        
        arsonist=TP->query_real_name();
        
        COFFINBURN_LOG("coffinburn_log",
                arsonist+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin on fire with hellfire under water. "+destructeeav2+".\n");
    
        write_file(LOG_DIR+"coffins",capitalize(arsonist)+" lit "+
        (strlen(owner) ? owner +"'s" : "an unclaimed") 
        + " coffin on fire with hellfire under water. "+destructeeav2+".\n");
        
        add_prop(OBJ_M_NO_GET,"You cannot pick up a burning coffin.\n");
        
        add_prop(CONT_I_LIGHT,3);
        
        on_fire=set_alarm(3.0,0.0,burn_it_underwater);
        
        return 1;
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
    
    COFFINBURN_LOG("coffinburn_log",arsonist+" lit "+
    (strlen(owner) ? owner +"'s" : "an unclaimed") + " coffin on fire. "+destructeeav2+".\n");
    
    write_file(LOG_DIR+"coffins",capitalize(arsonist)+" lit "+
    (strlen(owner) ? owner +"'s" : "an unclaimed") + " coffin on fire. "+destructeeav2+".\n");
    
    add_prop(OBJ_M_NO_GET,"You cannot pick up a burning coffin.\n");
    
    add_prop(CONT_I_LIGHT,3);
    
    on_fire=set_alarm(3.0,0.0,burn_it);
    
    return 1;
}


int
do_sigil(string str)
{
    if (str == "coffin with sigil")
    {
        if (COFFIN_OWNER(TP))
        {
            if (environment(this_player()) == this_object())
            {
                write("You can't enchant your "
                +"coffin while being in it!\n");
                
                return 1;
            }

            if (this_object()->query_sigil() == 1)
            {
                write("Your coffin is already protected by the sigil ward.\n");
            
                return 1;
            }
                        
            int bloodpool = VAMPIRES_MAPPINGS->query_thirst_gauge(this_player()->query_name());
                       
            if (bloodpool < 301)
            {
                write("This ward requires a substantial amount of blood, which "
                +"you currently don't have. Feed more.\n");
                
                return 1;
            }
            
            bloodpool = bloodpool - 299;
                       
            write("With the power of the blood, you silently enchant your "
            +"coffin with a strong protective ward.\nFor a brief "
            +"moment, it glows faintly before returning to normal.\nYou feel a "
            +"substantial amount of blood draining from your system and "
            +"into the protective ward!\n");
            
            sigil = 1;  
            save_coffin();
            
            VAMPIRES_MAPPINGS->set_thirst_gauge(this_player()->query_name(), bloodpool);
            
            return 1;
        }
        
        write("That protective sigil can only enchant "
        +"on your own coffin.\n");
        
        return 1;
    }
    
    write("Enchant what with sigil?\n");
    
    return 1;
}


int
stop_tenting(string str)
{
    if (str == "tent")
    {
        write("You can't use tents in here.\n");
        
        return 1;      
    }
    
    return 0;
}


void
init()
{
    //init_skill_raise();
    
    ::init();

    if (ENV(TP)==TO)
    {
        init_guild_support();
        add_action(rise,"rise");
        add_action(rise,"out");
        add_action(rise,"leave");
        add_action(start,"start");
        
        add_action(stop_tenting,"set");
        add_action(stop_tenting,"erect");
        
        add_action(do_blockskillraise, "learn");
        add_action(do_blockskillraise, "improve");
        add_action(do_blockskillraise, "train");
        return;
    }

    add_action(burn,"burn");

    if (!COFFIN_OWNER(TP) && !IS_WIZ(TP) && strlen(owner))
    {  
        return;
    }
    
    add_action(dispatch_coffin,"dispatch");

    add_action(enter, "enter");
    
    add_action(do_sigil,"enchant");
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


void
expel_vamp(object vamp)
{
    vamp->command("crawl up");
    vamp->expel_vampire();
}


public void surprise_vampire(object vampire,string destroyer)
{
    if (vampire->query_ghost())
    {
        return;
    }
    
    object torpor_room;
    
    vampire->add_prop(COFFIN_DESTROYED, 1);
    
    torpor_room = clone_object(ROOM_DIR+"torpor");
    
    vampire->move_living("M",torpor_room,1,1);
            
    COFFIN_MANAGER->remove_coffin(vampire->query_real_name());
    
    VAMPIRES_MASTER->add_aging_check(vampire->query_real_name());
    
    
    
    // Vampires can avoid being permanently destroyed by consuming 
    // a point of immortality. Only occ Vampires can gain such
    // points, so layman vampires will always be destroyed if
    // the coffin is destroyed while they are offline.  
    if (VAMPIRES_MAPPINGS->query_vampires_resilience(vampire->query_name()) > 0)
    {
        int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(vampire->query_name());
        int new_resilience_rank = current_resilience_rank - 1;
        
        VAMPIRES_MAPPINGS->set_vampires_resilience(vampire->query_name(), new_resilience_rank); 

        VAMPIRES_MAPPINGS->set_thirst_gauge(vampire->query_name(), 1);
        
        if (VAMPIRES_MAPPINGS->query_vampires_resilience(vampire->query_name()) == 0)
        {               
            clone_object(VAMPIRES_GUILD_DIR + "obj/immpoint_reward_obj")->move(vampire, 1);
        }
    
        vampire->catch_msg("Your coffin has been found and "
        +"destroyed!\nYou wake up somewhere "
        +"burrowed in the "
        +"ground, barely lingering to this "
        +"world while being greatly weakened!\nA point of "
        +"Immortality has been reducted to save you from "
        +"permanent destruction!\n");
        
        remove_ashes();
    
        return;         
    }
    
    //VAMPIRES_MASTER->remove_lay_vampires(vampire->query_name());
    
    VAMPIRES_MASTER->add_failed_vampire(vampire->query_name());
    
    clone_object(VAMPIRES_GUILD_DIR + "obj/expel_obj")->move(vampire, 1);
    set_alarm(1.0, 0.0, &expel_vamp(vampire));
    
    vampire->catch_msg("Your coffin has been found and "
    +"destroyed!\nYou wake up somewhere "
    +"burrowed in the "
    +"ground!\n");
    
    LEAVE_LOG("leave_log",
    "The Vampire (Spawn) " +vampire->query_name() 
    +" was destroyed due to waking up to a burned "
    +" coffin.\n");
    
    remove_ashes();
    
    CREATE_MAIL("Destruction", "Vampires", vampire->query_name(), "",
                "Your coffin was found and destroyed.\n");
                
    return;
}


public void enter_inv(object ob, object from)
{
    if (ob->query_ghost())
    {
        return;
    }
    
    object torpor_room;
    
    if (!IS_CLONE)
    {
        object * 
        mycoffins=filter(object_clones(TO),
            &operator (==) (ob->query_real_name(),) @ &->query_owner());
            
        if (sizeof(mycoffins)>0)
        {         
            int ownav = ob->query_average();
            
            COFFIN_MANAGER->set_owner_avg(ob,ownav);
            
            ob->move(mycoffins[0],1);
            
            return;
        }
        
        string location=COFFIN_MANAGER->query_location(ob);
        
        // If no coffin, we burrow the player in a random graveyard.
        if (!location || !strlen(location))
        {
            torpor_room = clone_object(ROOM_DIR+"torpor");
            
            ob->move_living("M",torpor_room,1,1);
            ob->catch_msg("You wake up somewhere burrowed in the "
                +"ground.\n");

            COFFIN_MANAGER->remove_coffin(ob->query_real_name());
            
            return;
        }
        
        LOAD_ERR(location);
        mycoffins=filter(object_clones(TO),
            &operator (==) (ob->query_real_name(),) 
            @ &->query_owner());
        

        // if we have a coffin, we are moved there.        
        if (sizeof(mycoffins)>0)
        {
            ob->move(mycoffins[0],1);
            
            return;
        }
        
        torpor_room = clone_object(ROOM_DIR+"torpor");
        
        ob->move_living("M",torpor_room,1,1);
        
        ob->catch_msg("You wake up somewhere burrowed in the "
            +"ground.\n");
        
        COFFIN_MANAGER->remove_coffin(ob->query_real_name());
        
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



