/*
 * Vitwitch's Robe  ... from the dark ocean deeps
 *
 * Vitwitch 10/2021
 *
 * Based on
 * Sateela's Robe, by Gwyneth, 06/16/99
 *
 *  ... but with a somewhat different effect
 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define WEAR_DURATION_SECS 3600
#define NUM_TELLS 20

static int gRemoveable = 0;
static int gNumTold = 0;

static float gTellPeriodSecs;

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
    set_short("robe of woven worms");
    set_pname("robes");
    set_pshort("robes of woven worms");
    set_adj("wet");
    add_adj("cold");

    set_long("This 'robe' is a wearable mass "+
             "of giant tubeworms. Perhaps they wove themselves together in "+
             "the darkness of the ocean deeps and perished in one another's embrace. "+
             "The robe is soaking wet and deep-ocean cold besides. "+
             "It clings hideously to the touch. It possesses a curious "+
             "aura of magicality.\n"); 

    set_ac(5);
    set_at(A_ROBE);

    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);

    add_prop(OBJ_M_NO_DROP,"Having picked it up, the robe of woven worms clings "+
              "wetly to you. Wearing it should dry it out.\n");

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
    tell_room(environment(p),"The robe crumbles to dust.\n\n");

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
    tell_room(environment(p), "A " + short() + " frays and falls apart on the body of " + 
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

    say(QCTNAME(p) + " slips on a " + short() + " . It clings to their body... " +
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
        write("The " + short() + " clings wetly to you and resists being removed. " +
          "In time it will probably dry out and fall apart.\n"); 
        say(QCTNAME(this_player()) + " tries to remove their " + short() + ", but fails.\n");
        return -1;
    }

    return 1;
}

