inherit "/std/object";
inherit "/lib/unique";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

#define SCROLL        "/d/Krynn/solamn/palanthas/merchants/obj/spell_tome"
#define HANDS         "/d/Krynn/solamn/palanthas/merchants/obj/ghoul_stun"
#define SPECTRE       "/d/Krynn/solamn/palanthas/merchants/living/shoikan_spectre"

int corpse_opened = 0;
int ghoul_cloned = 0;
object treasure, spectre;

void
create_object()
{
    set_name("corpse");
    set_short("half-buried decaying corpse");
    add_adj(({"half-buried","decaying","buried","half"}));
    set_long("Just within the perimeter of the enormous grim oaks that " +
        "make up the entry to the Shoikan Grove is the corpse of a " +
        "female human, half buried in the damp ground. The look on her " +
        "face is one of horror, indicating she did not die a particularly " +
        "pleasant death.@@tome_desc");
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_M_NO_GET, 1);

    add_item(({"tome","leather-bound tome"}),"@@exa_tome");

    add_cmd_item(({"tome from corpse", "leather-bound tome from corpse", 
        "tome from hand", "leather-bound tome from hand", 
        "tome from decaying corpse","leather-bound tome from decaying corpse",
        "leather-bound tome from half-buried decaying corpse",
        "tome from half-buried decaying corpse"}),
        ({"get","take","grab","pull"}),"@@take_tome");
    setuid; seteuid(getuid());
}

string
exa_tome()
{
    if(corpse_opened)
        return "Examine what?\n";
    else
        return "A leather-bound tome is clutched in the outstretched hand " +
            "of the corpse before you. You could probably take it.\n";
}

string
tome_desc()
{
    if(corpse_opened)
        return "\n";
    else
        return " Clutched in an outstretched hand is a leather-bound tome.\n";
}

void
remove_remains()
{
    tell_room(E(TO),"Ghoulish hands pull the decaying corpse into the " +
        "damp ground.\n");
    TO->remove_object();
}

void
create_spectre(object ob)
{
    spectre = clone_object(SPECTRE);
    int stat = ob->query_average_stat();
    spectre->set_stats(({stat+random(30), stat+random(50), stat+random(20),
        stat, stat, stat}));
    tell_room(E(TO),"With a deathly hiss, a shadowy spectre breaks " +
        "towards you from the darkness of the grove!\n");
    spectre->move(E(TO), 1);
    spectre->command("kill " +ob->query_real_name());
}

string
take_tome()
{
    if(corpse_opened)
    {
	return "There is nothing to take from the corpse?\n";
    }

    if(!ghoul_cloned)
    {
        object hands = clone_object(HANDS);
        hands->move(TP, 1);
        set_alarm(1.5, 0.0, &create_spectre(TP));
        ghoul_cloned = 1;
        return "";
    }

    if(objectp(spectre))
    {
        write("The guardian spectre is in between you and the " +
            "tome! You cannot reach it without going through - " +
            "literally - it!\n");
        return "";
    }

    treasure = clone_object(SCROLL);
    string tome = treasure->short();

    write("You reach out and pull the " +tome+ " from the deathly " +
        "grasp of " +TO->short()+ ".\n");
    say(QCTNAME(TP)+ " reaches out and gets a " + tome + 
          " from the outstretched hand of the " +TO->short()+ ".\n");

    treasure->move(TP, 1);
    corpse_opened = 1;

    set_alarm(45.0,0.0,&remove_remains());
    return "";
}
