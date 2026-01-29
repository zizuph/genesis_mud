inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "../lib/ranger_defs.h"

object  Recruiter,
        Recruit;
int     Accepted,
        Oath_Stage,
        Drama_alarm;

public int deadline();

public void
create_object()
{
    Oath_Stage = 0;
    Accepted = 0;
    set_no_show();
    set_name("_RoN_recruit_object_");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    set_alarm(30.0, 0.0, deadline);
}

void
set_recruiter(object o)
{
    Recruiter = o;
}

void
set_recruit(object o)
{
    Recruit = o;
}

void
enter_env(object to, object from)
{
    ::enter_inv(to, from);
    if (interactive(to))
        if (Recruit != to)
            remove_object();
}

public void
make_recruit()
{
    if (!Accepted)
        return;
    FIX_EUID
    NORTH_MASTER->new_member(Recruit, Recruiter->query_name());
    set_alarm(3.0, 0.0, remove_object);
}

public int
deadline()
{
    if (!Accepted)
    {
        if (objectp(Recruiter))
            Recruiter->catch_msg("Your offer to " + Recruit->query_name()
              + " received no answer.\n");
        if (objectp(Recruit))
            Recruit->catch_msg("You failed to respond to " + Recruiter->query_name()
              + "'s offer in time. It is now retracted.\n");
        remove_object();
    }
}

public void
recruitment_drama()
{
    /* This function takes care of the ceremony and oath a new member of
     * the Rangers of the North must take to join.
     */
    remove_alarm(Drama_alarm);
    Drama_alarm = 0;
    /* If the Ranger Captain and the recruit are no longer together in the
       same room, break off the process and reset everything by removing
       this object.
     */
    if (ENV(Recruit) != ENV(Recruiter))
    {
        Recruiter->catch_msg("You lost the recruit and will have to start over "
          + " again!\n");
        remove_object();
        return;
    }

    switch(Oath_Stage)
    {
        case 0:
          Recruit->catch_msg(Recruiter->query_name() + " clasps "
            + POSSESSIVE(Recruiter) + " hands around your clasped hands.\n");
          Recruiter->catch_msg("You clasp your hands around " 
            + Recruit->query_name() + "'s.\n");
          say(QCTNAME(Recruiter) + " clasps " + POSSESSIVE(Recruiter) + " hands around "
            + QTNAME(Recruit) + "'s.\n", ({ Recruit, Recruiter }));
          Oath_Stage = 1;
          break;
        case 1:
          Recruiter->command("$dsay Do you, " + Recruit->query_name() + ", wish to "
            + "join the kindred of the Rangers of the North?");
          Recruiter->command("$dsay If so, say 'I do.'");
          if (Recruiter->query_wiz_level())
          {
             say(QCTNAME(Recruiter) + " says: Do you, " + Recruit->query_name() +
              ", wish to join the kindred of the Rangers of the North?\n");
            say(QCTNAME(Recruiter) + " says: If so, say 'I do'.\n");
          }
          Oath_Stage = 2;
          break;
        case 3:
          Recruiter->command("$dsay Do you pledge to serve the Chieftain of the Rangers "
            + "of the North and his appointed Captain in all things, be they grim or "
            + "glad, until you are released from service?");
          if (Recruiter->query_wiz_level())
            Recruit->catch_msg(QCTNAME(Recruiter) + " says: Do you pledge to serve "
              + "the Chieftain of the Rangers of the North and his "
              + "appointed Captain in all things, be they grim or glad, "
              + "until you are released from service?\n");
          Oath_Stage = 4;
          break;
        case 5:
          Recruiter->command("$dsay Do you pledge to maintain the secrecy of the "
            + "Rangers of the North and guard the lives of your brethren as they "
            + "will guard yours?");
          if (Recruiter->query_wiz_level())
            Recruit->catch_msg(QCTNAME(Recruiter) + " says: Do you pledge to maintain the "
              + "secrecy of the Rangers of the North and guard the lives "
              + "of your brethren as they will guard yours?\n");
          Oath_Stage = 6;
          break;
        case 7:
          Recruiter->command("$dsay And do you pledge to hold the Valar in reverence "
            + "above all the Kings of the land, be they mortal men, elven lords, or "
            + "dark spirits of the Void?");
          if (Recruiter->query_wiz_level())
            Recruit->catch_msg(QCTNAME(Recruiter) + " says: And do you pledge to hold "
              + "the Valar in reverence above all the Kings of the land, "
              + "be they mortal men, elven lords, or dark spirits of "
              + "the Void?\n");
          Oath_Stage = 8;
          break;
        case 9:
          Recruiter->command("$dsay Arise then, " + Recruit->query_name()
            + ", Ranger of the North!");
          if (Recruiter->query_wiz_level())
            Recruit->catch_msg(QCTNAME(Recruiter) + " says: Arise then, "
              + Recruit->query_name() + ", Ranger of the North!\n");
          Oath_Stage = 10;
          break;
        case 10:
          Recruit->catch_msg(Recruiter->query_name() + " releases your hands and "
            + "gives you a star-shaped brooch of silver.\n");
          Recruiter->catch_msg("You release " + Recruit->query_name() + "'s hands and "
            + "give " + OBJECTIVE(Recruit) + " a grey cloak and a "
            + "star-shaped brooch.\n");
          say(QCTNAME(Recruiter) + " releases " + QTNAME(Recruit) + "'s hands and "
            + "gives " + OBJECTIVE(Recruit) + " a grey cloak and "
            + "a small silvery object.\n",
              ({ Recruit, Recruiter }));
          Recruit->catch_msg("You rise to your feet again.\n");
          Recruiter->catch_msg(Recruit->query_name() + " rises to " + POSSESSIVE(Recruit)
            + " feet again.\n");
          say(QCTNAME(Recruit) + " rises to " + POSSESSIVE(Recruit) 
            + " feet again.\n",
              ({ Recruit, Recruiter }));
          Oath_Stage = 100;
          make_recruit();
          break;
        default:
          return;
          break;
    }
    if (Oath_Stage != 100)
        Drama_alarm = set_alarm(5.0, 0.0, recruitment_drama);
}

public int
do_i_do(string str)
{
    object tp = TP;
    string vb = query_verb();

    if (wildmatch("'*", vb))
    {
        str = extract(vb, 1) + " " + str;
        vb = "say";
    }

    str = LOW(str);
    if (str != "i do" && str != "i do.")
        return 0;

    if (Oath_Stage != 2 && Oath_Stage != 4 && Oath_Stage != 6 && Oath_Stage != 8)
        return 0;

    Recruit->command("$dunsay I do.");
    Oath_Stage += 1;
    if (!Drama_alarm)
        Drama_alarm = set_alarm(5.0, 0.0, recruitment_drama);
    return 1;
}    

public int
accept_offer(string str)
{
    string Cname = Recruiter->query_name(),
           Rname = Recruit->query_name();

    if (!strlen(str) || str != "offer")
        NFN0("Accept what? The offer?");

    if (Accepted || Drama_alarm)
        NFN0("You have already accepted the offer!");

    write("You kneel before " + Cname + " and clasp your "
      + "hands together.\n");
    Recruiter->catch_msg(Rname + " kneels before you and clasps "
      + Recruit->query_possessive() + " hands together.\n");
    say(QCTNAME(TP) + " kneels before " + QTNAME(Recruiter)
      + " and clasps " + Recruit->query_possessive() + " hands "
      + "together.\n", ({ Recruit, Recruiter }));
    Accepted = 1;

    if (!Drama_alarm)
        set_alarm(3.0, 0.0, &recruitment_drama(0));
    return 1;
}

public int
decline_offer(string str)
{
    if (!strlen(str) || str != "offer")
        NFN0("Decline what? The offer?");

    write("You politely decline " + Recruiter->query_name() + "'s offer.\n");
    Recruiter->catch_msg(TP->query_name() + " politely declines your offer "
      + "to join the Rangers of the North.\n");
    remove_object();
    return 1;
}

public void
init()
{
    ::init();
    add_action("accept_offer", "accept");
    add_action("decline_offer", "decline");
    add_action("do_i_do", "say");
    add_action("do_i_do", "'", 1);
    add_action("do_i_do", "dsay");  /* Dunadan speech, Adunaic */
}

