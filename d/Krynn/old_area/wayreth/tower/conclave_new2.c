/*
   Wayreth.

   conclave.c
   ----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : March 19 1997 
   By ...........: Teth

*/

#include <macros.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/guild/local.h"
inherit TOWERROOM;

#define ADM    "/d/Krynn/wayreth/guild/admin/admin.c"
#define WHITE  ADM->query_conclave_head("white")
#define RED    ADM->query_conclave_head("red")
#define BLACK  ADM->query_conclave_head("black")
#define WOFFICE  WTOWER + "whitestudy"
#define ROFFICE  WTOWER + "redstudy"
#define BOFFICE  WTOWER + "blackstudy"
#define WHITE_ENTER "_i_may_enter_white"
#define RED_ENTER   "_i_may_enter_red"
#define BLACK_ENTER "_i_may_enter_black"

int check_whitehead();
int check_redhead();
int check_blackhead();


void
create_tower_room()
{
    set_short("Conclave board room and lobby");
    set_long("This is the area of the conclave of the mages of Wayreth. " +
      "Here the masters of the three factions of mages have " +
      "their private studies. White is to the north, Red is " +
      "to the west, and Black is to the south. A colored bell " +
      "cord hangs in front of each of the three offices of the " +
      "Wayreth conclave and an exit leads east to the stairwell.\n");

    AI(({"spectres","powerful spectres","spectre","guardian","subtle spectres"}),
      "Though you can't see them, you have no doubt that they'll make " +
      "their presence known should you attempt to enter an office unbidden.\n");

    AI(({"colored cord","cord","cords","bell cord","bell cords","colored bell cords"}),
      "Which bell cord? The white, red, or black cord?\n");
    AI(({"white cord","white bell cord","silk"}),
      "Pull this cord, made of thick, pure white silk, to ring the bell " +
      "inside the office of "+capitalize(WHITE)+", Master of the White " +
      "Robed Mages.\n");
    AI(({"red cord","red bell cord","satin"}),
      "Pull this cord, made of thick, vibrant crimson satin, to ring the " +
      "bell inside the office of "+capitalize(RED)+", Master of the Red " +
      "Robed Mages.\n");
    AI(({"black cord","black bell cord"}),
      "Pull this cord, made of thick, deep midnight velvet, to ring the " +
      "bell inside the office of "+capitalize(BLACK)+", Master of the " +
      "Black Robed Mages.\n");
    ACI(({"white","white cord","white bell cord"}),"pull", "@@do_pullwhite");
    ACI(({"red","red cord","red bell cord"}),"pull", "@@do_pullred");
    ACI(({"black","black cord","black bell cord"}),"pull", "@@do_pullblack");

    add_exit(WTOWER + "stairwell08", "east", 0);
    add_exit(WTOWER + "whitestudy", "north", check_whitehead);
    add_exit(WTOWER + "blackstudy", "south", check_blackhead);
    add_exit(WTOWER + "redstudy", "west", check_redhead);

    clone_object(WOBJ + "conclave_board")->move(this_object());
}

int
do_pullwhite()
{
    write("You pull the white bell cord and a faint ringing is " +
      "heard in the office to the north.\n");
    say( QCTNAME(TP)+" pulls the white bell cord and a " +
      "faint ringing is heard in the office to the north.\n");
    tell_room(WOFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
do_pullred()
{
    write("You pull the red bell cord and a faint ringing is " +
      "heard in the office to the west.\n");
    say( QCTNAME(TP)+" pulls the red bell cord and a " +
      "faint ringing is heard in the office to the west.\n");
    tell_room(ROFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
do_pullblack()
{
    write("You pull the black bell cord and a faint ringing is " +
      "heard in the office to the south.\n");
    say( QCTNAME(TP)+" pulls the black bell cord and a " +
      "faint ringing is heard in the office to the south.\n");
    tell_room(BOFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
check_whitehead()
{
    if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_WHITE)) || (TP->query_wiz_level()))
    {
        write("The spectral guardian obediently reports that no " +
          "one has entered your office since you left and humbly " +
          "steps aside as you enter your office.\n");
        say("The spectral guardian briefly reports to "+QTNAME(TP)+" and " + 
          "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
          " enters "+HIS(TP)+" office.\n");
        return 0;
    }
    if (TP->query_prop(WHITE_ENTER))
        return 0;
    if (!TP->query_prop(WHITE_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the White Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+QTNAME(TP)+
          " and with a touch halts all thoughts of continuing north.\n");
        return 1;
    }
}

int
check_redhead()
{
    if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_RED)) || (TP->query_wiz_level()))
    {
        write("The spectral guardian obediently reports that no " +
          "one has entered your office since you left and humbly " +
          "steps aside as you enter your office.\n");
        say("The spectral guardian briefly reports to "+QCTNAME(TP)+" and " +
          "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
          " enters "+HIS(TP)+" office.\n");
        return 0;
    }
    if (TP->query_prop(RED_ENTER))
        return 0;
    if (!TP->query_prop(RED_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the Red Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+QTNAME(TP)+
          " and with a touch halts all thoughts of continuing west.\n");
        return 1;
    }
}

int
check_blackhead()
{
    if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_BLACK)) || (TP->query_wiz_level()))
    {
        write("The spectral guardian obediently reports that no " +
          "one has entered your office since you left and humbly " +
          "steps aside as you enter your office.\n");
        say("The spectral guardian briefly reports to "+QCTNAME(TP)+" and " +
          "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
          " enters "+HIS(TP)+" office.\n");
        return 0;
    }
    if (TP->query_prop(BLACK_ENTER))
        return 0;
    if (!TP->query_prop(BLACK_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the Black Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+QTNAME(TP)+
          " and with a touch halts all thoughts of continuing south.\n"); 
        return 1;
    }
}

void
init()
{
    ADD("grant_person", "permit");
    ADD("grant_person", "grant");
    ADD("remit_person", "remit");
    ADD("remit_person", "revoke");
    ::init();
}


/* A function that allows conclave members to allow others into their
 * offices
 */

int
grant_person(string str)
{
    object target;

    NF("Wizards should add the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What ?\n");
    if (!IS_CONCLAVE(TP->query_real_name()))
        return 0;	

    NF("Grant whom permission to enter your office?\n");
    if (!str)
        return 0;

    if (!find_player(str) || !P(str, TO))
        return 0;

    target = P(str, TO);

    NF("You have already granted "+target->query_name()+".\n");
    if (((target->query_prop(WHITE_ENTER)) &&
        (TP->query_real_name() == WHITE)) ||
      ((target->query_prop(RED_ENTER)) &&
        (TP->query_real_name() == RED)) ||
      ((target->query_prop(BLACK_ENTER)) &&
        (TP->query_real_name() == BLACK)))
        return 0;

    if (TP->query_real_name() == WHITE)
        target->add_prop(WHITE_ENTER, 1);
    if (TP->query_real_name() == RED)
        target->add_prop(RED_ENTER, 1);
    if (TP->query_real_name() == BLACK)
        target->add_prop(BLACK_ENTER, 1);
    write("You permit "+target->query_the_name(TP)+" to " +
      "enter your office.\n");
    target->catch_msg(TP->query_The_name(target)+" permits you " +
      "to enter "+HIS(TP)+" office.\n");
    return 1;
}

int remit_person(string str)
{
    object target;

    NF("Wizards should remove the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What ?\n");
    if (!IS_CONCLAVE(TP->query_real_name()))
        return 0;	

    NF("Revoke whom permission to enter your office?\n");
    if (!str)
        return 0;

    if (!find_player(str) || !P(str, TO))
        return 0;

    target = P(str, TO);

    NF("That person does not currently have permission.\n");
    if (((!target->query_prop(WHITE_ENTER)) &&
        (TP->query_real_name() == WHITE)) ||
      ((!target->query_prop(RED_ENTER)) &&
        (TP->query_real_name() == RED)) ||
      ((!target->query_prop(BLACK_ENTER)) &&
        (TP->query_real_name() == BLACK)))
        return 0;

    if (TP->query_real_name() == WHITE)
        target->remove_prop(WHITE_ENTER);
    if (TP->query_real_name() == RED)
        target->remove_prop(RED_ENTER);
    if (TP->query_real_name() == BLACK)
        target->remove_prop(BLACK_ENTER);
    write("You revoke permission for "+target->query_the_name(TP)+" to " +
      "enter your office.\n");
    target->catch_msg(TP->query_The_name(target)+" revokes permission " +
      "for you to enter "+HIS(TP)+" office.\n");
    return 1;
}
