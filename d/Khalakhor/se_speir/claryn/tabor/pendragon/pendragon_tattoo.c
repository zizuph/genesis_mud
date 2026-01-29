
/*
 * The tattoo that is written
 * on a Librarian by a Pendragon
 * Vitwitch 09/2020
 *
 * updated 04/2021 to NOT be wearable object -- Vitwitch 
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()
#define NF(xxx) notify_fail(xxx)

/*VW
#define PENDRAGON_PATH "/w/vitwitch/pendragon/local/"
VW*/

#define PENDRAGON_PATH "/d/Khalakhor/se_speir/claryn/tabor/pendragon/"

/* do not change NAME nor ADJ */ 
#define PENDRAGON_NAME "pendragon"
#define PENDRAGON_ADJ "inky"

string my_message = "";
string my_colour = "";
string recover_string = "";

/* prototype */
void set_tattoo_data(string data);

void
create_object()
{
}

void
appraise_object(int num)
{
    write(this_object()->long() + "\n");
    write("You " + APPRAISE_VERB + " that the weight is " +
        appraise_weight(num) + " and you " + APPRAISE_VERB +
        " its volume is about " + appraise_volume(num) +
        ". You estimate its worth to " + appraise_value(num) + "." +
        appraise_light(num));
    if (this_object()->check_recoverable() != 1)
    {
        write(" " + capitalize(LANG_THESHORT(this_object())) +
            " does not seem to be able to last a while.");
    }
    if (this_object()->query_keepable())
    {
        write(this_object()->appraise_keep(num));
    }
    write("\n");

    if (this_object()->query_item_expiration())
        write(appraise_item_expiration() + "\n");
}


void
set_tattoo_data(string data)
{

    string foo, bar;

    seteuid(getuid());

    sscanf(data, "%s&&%s&&%s&&%s", 
     foo, my_colour, my_message, bar);
    if (sizeof(explode(data, "&&")) < 3)
        sscanf(data, "%s&&%s", my_colour, my_message);

    set_name("dragon tattoo");
    set_pname("dragon tattoos");
    add_name("tattoo");
    add_name("dragon tattoo etched in flesh");

    set_adj("etched in flesh");

    set_short("dragon tattoo etched in flesh");
    set_pshort("dragon tattoos etched in flesh");

    add_prop(OBJ_I_NO_DROP, 
       "You cannot drop a dragon tattoo -- it is of your flesh --" +
              " you must <scour> it.\n");

    remove_prop(OBJ_I_VALUE);

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_STEAL,0);
    add_prop(OBJ_I_NO_BUY,0);
    add_prop(OBJ_I_NO_SELL,0);
    add_prop(OBJ_I_NO_GIVE,0);
    add_prop(OBJ_I_NO_MAGIC,0);

    set_long("@@my_long");

    remove_item_expiration();

    set_may_recover();

    recover_string = "&&" + my_colour + "&&" 
                + my_message + "&&";

}

string
my_long()
{
    return "A dragon tattoo runs"+
           " in elegant cursive runes of " + my_colour + ":\n\n ~~~  "
            + my_message + "    ~~~\n\n"; 
}

void
set_writing_data(string colour, string text)
{
    string init_string;
    my_message = text;
    my_colour = colour;
    init_string = "&&" + colour + "&&" + text + "&&";
    set_tattoo_data( init_string );
}

int
read(string str)
{
    if( (str == "tattoo") || (str == "pendragon tattoo") ) {
       write("A pendragon's cursive whorls are not for reading." +
            " You must <examine> the dragon tattoo.\n");
       return 1;
  }
  else
  {
      return 0;
  }

}

public void
remove_object()
{
    if (environment(this_object()))
        environment(this_object())->leave_inv(this_object(),0);
    this_object()->leave_env(environment(this_object()),0);
    destruct();
}

int
scour_it(string str)
{
    if(!strlen(str))
    {
        write("Scour what?\n");
        return 0;
    }
    if( str == "tattoo" || str == "dragon tattoo" )
    {
        write("You scour the dragon tattoo from your flesh with a grimace --" +
         " removing its elegant " + my_colour + " cursive whorls.\n");

        say(QCTNAME(this_player()) +" scours a dragon tattoo from their flesh.\n");

        remove_object();
        return 1;
    }
}

int
summon_it(string str)
{
    string librname;
    object pendrg;

    int iobj;
    object *ownerobj;

    if(!strlen(str))
    {
        return 0;
    }
    if( str == "dragon" )
    {
        write("Summon pendragon?.....");
        return 0;
    }
    if( str == "pendragon" )
    {

        ownerobj = all_inventory(this_player());

        for (iobj=0;iobj<sizeof(ownerobj);iobj++) 
        {
            if ( lower_case(ownerobj[iobj]->query_name()) == PENDRAGON_NAME )
            {

               if ( lower_case(ownerobj[iobj]->query_adj(0)) == PENDRAGON_ADJ )
               { 
                   write("Your pendragon waves a wing-tip before you," +
                   " thinking that you had forgotten she was there," +
                   " and that one pendragon is enough for anyone.\n");

                   say("A pendragon gestures anxiously to "
                      + QTNAME(this_player()) +".\n");

                   return 1;
               }

           }
        }

        write("The flapping shape of a pendragon appears abruptly" +
        " in mid-air in a swirling cloud of " + my_colour + " ink drops." +    
        " She lands upon your shoulder"+
        " and wraps her tail about your neck." +
        " She is ever eager to <dragon_tattoo> your flesh." +
        " She will also take a message.\n");

        say("A pendragon appears to " + QTNAME(this_player()) +".\n");

        setuid();
        seteuid(getuid());
        pendrg = clone_object(PENDRAGON_PATH + PENDRAGON_NAME);

        librname = lower_case(this_player()->query_real_name());

        pendrg->move(this_player(),1);
        pendrg->assign_librarian_name( librname );
        pendrg->assign_ink_colour( my_colour );

        return 1;
    }
}

string
query_recover()
{
    return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    set_tattoo_data(arg);
}


void
init()
{
   ::init();
    add_action("read","read");
    add_action("scour_it","scour");
    add_action("summon_it","summon");
}
