inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include <stdproperties.h>
#include <ss_types.h>

void
create_container()
{
    set_name("strongbox");
    set_adj("small");
    add_adj("gem-encrusted");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(7111999);  // There is no key for this strongbox

    set_pick(100);

    add_prop(OBJ_I_VALUE,12000);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 5500);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This gem-encrusted strongbox is " +
                      "protected with magical spells of protection, " +
                      "only opening when a specific incantation is " +
                      "recited.\n", 25, "The incantation to open " +
                      "this strongbox is 'hitimperakdarah'.\n", 60 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_cmd_item("hitimperakdarah","recite","@@unlock_strongbox");

    add_item("lock", "The strongbox is locked, but has no keyhole! You " +
                "wonder how it could be opened.\n");
}

string
unlock_strongbox()
{
    if(!TO->query_prop(CONT_I_LOCK))
      return "The gem-encrusted strongbox is already unlocked! No point " +
             "in reciting the incantation now.\n";

    if(TP->query_skill(SS_SPELLCRAFT) < 40)
    {
      say(QCTNAME(TP)+ " badly bumbles an attempt to recite a magical " +
          "incantation.\n");
      return "You bumble your attempt to recite this magical " +
          "incantation. You need more skill in spellcraft to " +
          "be able to recite it properly.\n";
    }

    if(TP->query_skill(SS_FORM_ABJURATION) < 20)
    {
      say(QCTNAME(TP)+ " badly bumbles an attempt to recite a magical " +
          "incantation.\n");
      return "You bumble your attempt to recite this magical " +
          "incantation. You need more skill in abjuration to be able " +
          "to dispel the protections cast over this strongbox.\n";
    }

    TO->remove_prop(CONT_I_LOCK);
    say(QCTNAME(TP)+ " recites a magical incantation over the " +
             "gem-encrusted strongbox. It glows briefly and then " +
             "unlocks!\n");
    return "You recite a magical incantation over the gem-encrusted " +
           "strongbox. It glows briefly and then unlocks!\n";

}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the strongbox.\n");
	return;
    }
    ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}


string
short_descr()
{
    return "small gem-encrusted strongbox";
}

string
long_descr()
{
    return "This is a small gem-encrusted strongbox that would be worth " +
           "a fortune in its own right, making you wonder what is " +
           "inside! the red gems covering the strongbox seem to glow " + 
           "with a magical light.\n";
}
