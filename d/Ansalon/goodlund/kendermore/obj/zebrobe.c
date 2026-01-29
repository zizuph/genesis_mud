/*
 * Based on
 * Sateela's Robe, by Gwyneth, 06/16/99
 *
 *  Vitwitch 10/2021:
 *   Zeboim's Robe  ... from the dark ocean deeps
 *   sought after item in a new quest given by Sateela
 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#define ROBEOFWOVENWORMS "_zeboim_robe_of_woven_worms"
#define WEAR_DURATION_SECS 3600
#define NUM_TELLS 20

static int gRemoveable = 0;
static int gNumTold = 0;

static float gTellPeriodSecs;

/* PROTOTYPES */

int is_torch( object obj );

/* FUNCTIONS */

void
announce_robe( object p )
{
    gNumTold++;
    tell_room(environment(p),"Something hideous this way came...\n");
    if ( gNumTold < NUM_TELLS ) 
        set_alarm( gTellPeriodSecs, 0.0, &announce_robe(p) );
}

void
create_armour()
{
    set_name("robe");
    add_name(ROBEOFWOVENWORMS);

    set_short("robe of woven worms");
    set_pname("robes");
    set_pshort("robes of woven worms");
    set_adj("wet");
    add_adj("cold");

    set_long("This 'robe' is a wearable mass "+
             "of giant tubeworms. Perhaps they wove themselves together in "+
             "the darkness of the ocean deeps and perished in one "+
             "another's embrace. "+
             "The robe is soaking wet and deep-ocean cold besides. "+
             "It clings hideously to the touch. It possesses a curious "+
             "aura of divine magicality.\n"); 

    set_ac(5);
    set_at(A_ROBE);

   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

   add_prop(OBJ_S_WIZINFO,"This item counteracts the magic of the "+
             "witch Sateela's robe. While worn, it sets the player's "+
             "appearance_offset to 50 -- enough to make someone appear "+
             "hideous. If worn for an hour of game time, it will dry out "+
             "and fall off. When this happens, it resets the player's "+
             "appearance_offset to 0, no matter what it was before, which "+
             "is the neutral setting. Twenty times over the course of "+
             "the hour of game time, the robe will tell the room in which "+
             "the player stands 'Something hideous this way came...'\n");

   add_prop(MAGIC_AM_ID_INFO,
       ({"This robe is the product of divine divising. Wearing it "+
       "until it dries out acts to remove any uglifying agents from the " +
       "wearer, cleansing them.\n", 20 }) );

    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);

    add_prop(OBJ_M_NO_DROP,"Having picked it up, the robe of woven "+
              "worms clings "+
              "wetly to you. Wearing it or burning it should dry it out.\n");

    gTellPeriodSecs = itof( WEAR_DURATION_SECS ) / itof( NUM_TELLS );

    set_af(this_object());
    seteuid(getuid(this_object()));
}


public void
hook_smelled(string str)
{
    write("The scent of salt and sea floor muck fills your nostrils.\n");
}


void
announce_remove( object p )
{
    tell_room(environment(p),"The robe's remains crumble to nothing.\n\n");

    gRemoveable = 1;
    remove_object();

    return;
}


void
remove_this_robe( object p )
{
    if ( environment(this_object()) != p || p != this_player() )
        return;

    p->catch_msg("\n\nYour " + short() + " has dried out -- it frays " +
                 "and falls apart.\n");
    tell_room(environment(p), "A " + short() 
            + " frays and falls apart on the body of " + 
               QTNAME(p) + ".\n",p);
 
    p->set_appearance_offset(0);
    p->catch_msg("\nYou look quite like your old self again.\n"); 

    set_alarm( 3.0, 0.0, &announce_remove(p) );

    return;
}


mixed
wear(object what)
{
    if (what != this_object())
        return 0;

    object p = this_player();
    string unattr = "a rotten fish on a platter at your name-day banquet";

    write("You slip on the " + short() + ". It clings hideously to your " +
          "body. In it you are as attractive as " + unattr + " ... ugh!\n");

    say(QCTNAME(p) + " slips on a " + short() + 
        " . It clings to their body... " +
         "wetly... hideously... ugh!\n"); 

    p->set_appearance_offset(50);

    float duration = itof( WEAR_DURATION_SECS );
    set_alarm( duration, 0.0, &remove_this_robe(p) );
    set_alarm( 1.0, 0.0, &announce_robe(p) );

    return 1;
}


mixed
remove( object what )
{
    if (what != this_object() || !this_player())
        return 0;

    if ( !gRemoveable ) 
    {
        write("The " + short() 
          + " clings wetly to you and resists being removed. " +
          "In time it will probably dry out and fall apart.\n"); 
        say(QCTNAME(this_player()) + " tries to remove their " + short() + 
                   ", but fails.\n");
        return -1;
    }

    return 1;
}


int
is_torch( object obj )
{
    return IS_TORCH_OBJECT(obj);
}


int
burn_it( string str )
{
    object p = this_player();

    if ( environment(this_object()) != p )
        return 0;

    if ( !strlen(str) )
        return 0;

    if ( !wildmatch("*robe of woven worms*",lower_case(str)) )
    {
        write("Burn what? The " + short() + "?\n");
        return 1;
    }

    // must have a torch to be able to burn the robe

    if ( sizeof( filter(deep_inventory(p),&is_torch()) ) == 0 )
    {
        p->catch_msg("\n\nTo burn the " + short() + " you need a torch...\n\n");
        tell_room(environment(p), QCTNAME(p) + " makes to burn a " + short() 
            + " but cannot find a torch to burn it with.\n", p);
        return 1;
    }

    p->catch_msg("\n\nYou manage to set the clinging " + short() +
                 " alight! It quickly dries out -- frays " +
                 "and falls apart in a smouldering heap.\n");
    tell_room(environment(p), "A " + short() 
            + " burns and frays and falls apart on the body of " + 
               QTNAME(p) + ".\n",p);
 
    set_alarm( 3.0, 0.0, &announce_remove(p) );

    return 1;
}


void
init()
{
    ::init();
    add_action(burn_it,"burn");
}

