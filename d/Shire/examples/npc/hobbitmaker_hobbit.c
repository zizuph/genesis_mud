//  Add the local and hobbitmaker defines
#include "../local.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

/*  This hobbit inherits the hobbitmaker... all hobbits in the shire
 *  should use this file, it makes generation of hobbits much easier and 
 *  gives you more time to create rooms *grin*  If you don't want a generic
 *  hobbit or want to alter what the typical hobbitmaker hobbit does
 *  inherit the hobbitmaker and redfeine the functions you want to change
 *  In this example I wanted to add a title to my hobbit change the 
 *  way the hobbit introduces itself and what the hobbit wears.
 *  -Igneous-
 */
void
create_hobbit()
{
    set_power(100); // This sets the nps stats and skills
    set_type(CITIZEN); // Sets the npc type and equipment
    set_name("bilbo");
    set_family_name("baggins");  // Biblo Baggins, how originial *grin*.
    set_gender(0);               // Better make sure he is a male hobbit.
    set_title("the Innkeeper of the Brandywine Inn");
}

//  I want to change the default introduce for this hobbit
void
introduce_hobbit(string name)
{
    command("introduce myself to "+name);
    command("say Welcome to my Inn.");
}

//  I also want to change the default weapons and armours
void
arm_hobbit()
{
    object hat;

    FIXEUID;  //  Need to add this before you clone anything.
    hat = clone_object(EXAMPLE_ARM+"hobbit_hat");
    hat->move(TO);
    command("wear all");
}
