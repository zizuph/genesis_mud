/* Ashlar, 30 Jun 97 - A scarf seller */

#include "/d/Ansalon/common/defs.h";
#include "/d/Ansalon/taman_busuk/neraka/local.h";
#include "/sys/money.h"
#include <macros.h>
#include <composite.h>
#include <language.h>

inherit "/lib/trade";
inherit OUTER_IN;

#define SCARF   NARM + "scarf"
#define PRICE   5
/* price in silver coins */

#define DELAY 5.0

string *colours;
mixed *types;

object scarf_production;
object deliver_to;
int in_production;

object gnome;
object machine;

void
reset_neraka_room()
{
    if (!objectp(machine))
    {
        machine = clone_object(NOBJ + "dyemachine");
        colours = machine->query_colours();
        types = machine->query_types();
        machine->move(TO);
    }
    if (!objectp(gnome))
        gnome = clone_npc(NNPC + "dye_gnome");
}

void
create_neraka_room()
{
    set_short("scarf seller's shack");
    set_long("You stand within a small shack. The interior is covered in " +
        "all manner of colours. A sign hangs upon a wall, bearing " +
        "instructions of some kind.\n");

    add_item_inside();

    add_cmd_item("sign","read","@@sign");
    add_item("sign","@@sign");
    config_default_trade();

    in_production = 0;

    add_exit(NOUTER + "white/w6", "southeast", "@@go_se");

    reset_room();
}

int
go_se()
{
    write("You leave the small shack and emerge onto the market square.\n");
    return 0;
}

string
sign()
{
    string s;

    s = "Scarves for sale!\nWith the new amazing scarf dyeing machine, I " +
        "can offer you scarves in the following colours: " +
        COMPOSITE_WORDS(colours) + ".\nThe scarves can be decorated in " +
        "the following optional styles: " + COMPOSITE_WORDS(types) +
        ".\n\nTo order a scarf, just\n" +
        "  order <colour> scarf\n" +
        "or\n" +
        "  order <colour> scarf with <colour 2> <style>\n" +
        "\nFor example: order white scarf, order blue scarf with green stripes\n";
    return s + "\nAll scarves cost " + PRICE + " silver coins.\n";
}


void
init()
{
    ::init();
    add_action("do_order","order");
}

object
parse_order(string str)
{
    int r;
    string c1,c2,type,a,*b;
    object scarf;

    NF("The gnome says: OhDearSomethingIsWrongWithTheMachine!\n");
    if (!str)
     return 0; // because there were some strange runtimes
    
    r = sscanf(str, "%s scarf with %s",c1,a);
    if (r < 1)
    {
        r = sscanf(str, "%s scarf", c1);
        if (r < 1)
        {
            NF("Order what?\n");
            return 0;
        }
        if (member_array(c1,colours) == -1)
        {
            NF("The gnome says: IDon'tHaveThatKindOfDye.\n");
            return 0;
        }
        scarf = clone_object(SCARF);
        scarf->set_colour(c1);
        return scarf;
    }
    b = explode(a," ");
    c2 = b[0];
    type = implode(b-({c2})," ");
    if ((member_array(c1,colours)==-1) || (member_array(c2,colours) == -1))
    {
        NF("The gnome says: IDon'tHaveThatKindOfDye.\n");
        return 0;
    }
    if (member_array(type,types) == -1)
    {
        NF("The gnome says: MyMachineCannotDoThatStyle.\n");
        return 0;
    }
    scarf = clone_object(SCARF);
    scarf->set_colour(c1);
    scarf->set_colour2(c2);
    scarf->set_type(type);
    return scarf;
}

void
manufacture_scarf(int l)
{
    string s = "";
    if (!objectp(gnome))
    {
        tell_room(TO,"The machine grinds to a halt.\n");
        return;
    }
    if (!objectp(machine))
        return;

    switch(l++)
    {
        case 0:
            gnome->command("emote turns a knob and opens a valve.");
            break;
        case 1:
            gnome->command("emote pulls a lever and the machine starts to wheeze.");
            break;
        case 2:
            s = "The machine goes: Chug chug chug, amid clouds of steam.\n";
            break;
        case 3:
            s = "A bell rings in the machine, and " + QTNAME(gnome) +
                " pushes some buttons, seemingly at random.\n";
            break;
        case 4:
            if (random(2))
                gnome->command("worry");
            else
                gnome->command("say ThisUsuallyFails.");
            break;
        case 5:
            s = "The machine creaks and groans.\n";
            break;
        case 6:
            if (!random(3))
            {
                s = "You hear a great tearing sound, and the machine spits " +
                    "out a few remains of a scarf. " + QCTNAME(gnome) +
                    " sighs remorsefully, then inserts a new scarf into " +
                    "the machine.\n";
                l = 0;
                break;
            }
            s = "A cloud of steam exits from a valve, and " + QTNAME(gnome) +
                " looks relieved.\n";
            break;
        case 7:
            s = "A bell rings in the machine and a hatch opens. " +
                QCTNAME(gnome) + " fetches something from the open hatch.\n";
            l = 99;
            break;
    }
    tell_room(TO,s);
    if(l<99)
    {
        set_alarm(DELAY,0.0,&manufacture_scarf(l));
        return;
    }
    in_production = 0;
    if ((!objectp(deliver_to)) || (E(deliver_to) != TO))
    {
        tell_room(TO,"The buyer of the scarf is no longer present, so " +
            QTNAME(gnome) + " throws away the " + scarf_production->short() +
            ".\n");
        scarf_production->remove_object();
    }

    deliver_to->catch_msg(QCTNAME(gnome) + " gives you your " +
        scarf_production->short() + ".\n");
    tell_room(TO,QCTNAME(gnome) + " gives " + QTNAME(deliver_to) + " " +
        POSSESSIVE(deliver_to) + " " + scarf_production->short() +
        ".\n",deliver_to);
    if (scarf_production->move(deliver_to))
    {
        deliver_to->catch_msg("The scarf is too heavy, and you drop it.\n");
        scarf_production->move(E(deliver_to));
        tell_room(TO,QCTNAME(deliver_to) + " cannot carry " +
            POSSESSIVE(deliver_to) + " scarf, so " + PRONOUN(deliver_to) +
            " drops it.\n",deliver_to);
    }
    return;
}           

/* order <colour> scarf, order <colour> scarf with <colour2> <type> */
int
do_order(string str)
{
    int value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;
    object item;
    object ob;

    if (!objectp(gnome))
    {
        NF("There is noone here to take your order.\n");
        return 0;
    }

    if (in_production)
    {
        NF("The gnome says: SorryButIAmMakingAnotherScarfNowPleaseWait!\n");
        return 0;
    }

    if (!(ob = parse_order(str)))
        return 0;

    value = 5*12;

    if (sizeof(money_arr = pay(value,TP, "", 0, gnome, "")) == 1)
    {
        ob->remove_object();
        return 0;
    }
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    TP->catch_msg("You pay " + QTNAME(gnome) + " " + coin_pay_text + ".\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " in return.\n");

    scarf_production = ob;
    in_production = 1;
    deliver_to = TP;

    tell_room(TO,QCTNAME(gnome) + 
        " fetches a scarf from a box and inserts it into the machine.\n");

    set_alarm(DELAY,0.0,&manufacture_scarf(0));
    return 1;
}

