
/*
 *  /d/Ansalon/estwilde/obj/brewcraft_beervessel_rare1.c
 *  Beer crafted by mortal apprentices to the...
 *  ....Brewcrafter at the Iron Delving Brewery
 *
 *  Recoverable item
 *
 *  Based on brewcraft_beervessel_empty.c
 *   it is the seldom-found special version
 * 
 *  This is a reward item obtainable from brewery5.c
 *
 *  Vitwitch 03/2021
 */

#pragma strict_types
inherit "/std/object";
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

#define BLS_VESSEL_ID "_brewcraft_beer_vessel_blister"

static mapping invulnerable = 
   (["Union of the Warriors of Shadow":"Jazur intercedes!"]);

/* PROTOTYPES */

string query_recover();
void init_recover(string arg);
varargs void deliver_intox( object plyr, object thisp );
public void hook_smelled(string str);
int shatter_it(string inpstr);
public void enter_env(object dest, object old);
void init();

/* FUNCTIONS */

string
query_recover()
{
    return MASTER + ":" + "noSU";
}

void
init_recover(string arg)
{
}


public void
create_object()
{
    set_name("blistered vessel");
    add_name(BLS_VESSEL_ID);
    set_adj("crystal");

    set_short("blistered crystal vessel"); 
    set_pshort("blistered crystal vessels"); 

    set_long("" +
      "This is a crystal vessel, seemingly intended to be "+
      "shaped like a "+
      "deep-draught canoe. However it has been warped by "+
      "application of furious energies. Holding its "+
      "stem and stern in each hand, you can see "+
      "that at its twisted centre lies a large blister "+
      "in its crystal form. There is a burnt mosaic upon it "+
      "and a trace of scent about it.\n");

    add_item(({"mosaic"}),
      "The mosaic upon the vessel is of lapis lazuli "+
      "and depicts two broad rivers of blue -- it has been "+
      "burnt by the application of powerful energies. There "+
      "is a large blister in the crystal under the mosaic.\n");

    add_item(({"blister","large blister"}),
      "The large blister within the crystal of the vessel takes "+
      "up the bulk of its volume. A closer look reveals it seems to "+
      "contain a generous quantity of fine brew. The blister and the "+
      "brew within flickers from time to time with tiny fingers of "+
      "lightning. Perhaps you could <shatter> the vessel to release "+
      "this portentious brew.\n");

    add_prop(OBJ_M_NO_SELL,1);

    add_prop(OBJ_M_NO_DROP,"The blistered vessel is bound "+
       "to you by unseen force. You seem unable to cast it "+
       "from you by any means. You suppose that you could "+
       "<shatter> it to make it disappear.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 50);

    add_prop(MAGIC_AM_ID_INFO,
        ({ "This vessel allows the holder, who shatters it, "+
           "to intoxicate all players in the room, once.", 60}));

    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));

    add_prop(OBJ_S_WIZINFO,
       "This item is rarely encountered when drinking in the Iron Delving "+
       "Brewery. " +
       "It has no direct combat usage. It is available to all players. "+
       "It is not "+
       "transferrable between players. It recovers. It intoxicates all "+
       "players in " +
       "the room of its holder when it is destroyed.\n");

    set_may_recover();
    remove_item_expiration();

}

public void
hook_smelled(string str)
{
    write("A scent of malt and aromatic "+
           "cedar tantalises the nose.\n");
}

void
stop_retox()
{
    return;
}

void
deliver_intox( object trgt, object thisp )
{
    int maxintox;
    string str0, str1;
    string guildname = trgt->query_guild_name_occ();

    if ( !interactive(trgt) ) return;
    if ( !invulnerable[guildname] ) 
    {
        maxintox = trgt->query_prop(LIVE_I_MAX_INTOX);
        trgt->set_intoxicated(maxintox);
        trgt->catch_msg("A wave of obliviation engulfs you!\n");
    }
    else
    {
        str0 = " The shockfront approaching ";
        str1 = " is deflected!\n";

        thisp->catch_msg( invulnerable[guildname] + str0
               + QTNAME(trgt) + str1);
        trgt->catch_msg( invulnerable[guildname] + str0
               + "you"  + str1);
        tell_room(environment(thisp), invulnerable[guildname] + 
              str0 + QTNAME(trgt) + str1, ({thisp,trgt}) );
    }
    return;
}


int
shatter_it( string inpstr )
{
    string str;
    object tp = this_player();

    if ( !inpstr || !strlen(inpstr) )
    {
        write ("Shatter what? Shatter the blistered vessel?\n");
        return 0;
    }

    if ( inpstr != "blistered vessel" 
         && inpstr != "the blistered vessel" ) return 0;

    object *intoxers = FILTER_PLAYERS(all_inventory(environment(tp)));

    str = " a blistered crystal vessel! A shockfront "+
      "of brew expands to engulf all in an instant.\n";
    tp->catch_msg("You shatter" + str);
    tell_room(environment(tp), QCNAME(tp) + " shatters" + str, tp);

    foreach(object intoxer: intoxers)
    {
        deliver_intox(intoxer,tp);
    }

    tell_room(environment(tp), "The backdraft from the shattered "+
      "vessel leaves all a bit wobbly in its wake.\n");

    this_object()->remove_object();

    return 1;
}


public void
enter_env(object dest, object old)
{
    string fmtstr;
    ::enter_env(dest, old);

    if (interactive(dest))
    {
        dest->catch_msg("Receiving the vessel in your "+
        "hands, it pulses with an oblivial aura. " +
        "You feel its power bind to you.\n");

        // depending on how many other blistered vessels are
        // in the receiver's inventory... the vessel may 
        // spontaneously shatter

        int nblsv = sizeof( filter(deep_inventory(dest),&->id(BLS_VESSEL_ID)) );

        if ( nblsv > 1 ) 
        {
            int outcome = random(6) - nblsv;
            string magn;

            switch ( outcome )
            {
            default:
                magn = "catastrophically";
                break;
            case 0:
                magn = "dangerously";
                break;
            case 1:
                magn = "violently";
                break;
            case 2:
                magn = "significantly";
                break;
            case 3:
                magn = "slightly";
                break;
            }

            dest->catch_msg("The vessel vibrates " + magn + 
                    " in the presence of the "+
                    "other blistered vessels in your possession!\n");

            if ( outcome < 0 )
            {
                // accidental shatter

                object *intoxers = 
                         FILTER_PLAYERS(all_inventory(environment(dest)));

                string str = " blistered crystal vessel shatters "+
                  "from catastrophic vibration! A shockfront "+
                  "of brew expands to engulf all in an instant.\n";

                dest->catch_msg("Your" + str);

                tell_room(environment(dest), QTPNAME(dest) + str, dest);

                foreach(object intoxer: intoxers)
                    deliver_intox(intoxer,dest);

                tell_room(environment(dest), "The backdraft from the shattered "+
                     "vessel leaves all a bit wobbly in its wake.\n");

                this_object()->remove_object();
            }
            else
                dest->catch_msg("The vibration subsides and all is well.\n\n");
        }
 
    }
    return;
}


int
drink_it( string str )
{
    if ( !str || !strlen(str) ) return 0;

    if ( str == "blistered vessel" || str == "the blistered vessel" )
    {
        write( "There is nothing to drink. What brew there is, is sealed inside "+
        "the crystal blister. It would probably be released if the vessel were "+
        "shattered.\n");
        return 1;
    }

    return 0;
}


void
init()
{
    ::init();
    add_action("shatter_it","shatter");
    add_action(drink_it,"drink");
}
