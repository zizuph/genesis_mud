/* Removed the message that alerted Gorboth when runes were read */
string
exa_runes()
{
    string  ptxt;

    if (TP->query_skill(SS_AWARENESS) < 45)
    {
    return BSN("You find no such thing.");
    }

    if (TP->query_skill(SS_LANGUAGE) < 30)
    {
        ptxt = "The runes have been carved with great care into the"
             + " dark surface of the wall. Though you can clearly make"
             + " out their shape and form, their meaning is beyond your"
             + " ability to understand.";
    }

    else
    {
        ptxt = "The runes have been carved with great care into the"
             + " dark surface of the wall. They read:\n\n"
             + "\tThe voice of a Servant - The word of Opening\n\n"
             + "\t\t\t  ECHANNON";
    }

    return ptxt + "\n";
}

string
exa_opening()
{
    string  otxt = "Something is odd here.";

    if (opening)
    {
        return BSN(otxt + passage_text);
    }

    return BSN("You find no such thing.");
}

string
exa_wall()
{
    string  wtxt = "The wall rises a great distance running east and"
                 + " west along the outer perimeter of Minas Morgul."
                 + " Deep shadows cling to the wall as if they had been"
                 + " placed there by some Dark Sorcery.";

    if (opening)
    {
        wtxt += passage_text;
    }

    return BSN(wtxt);
}

string
exa_shadows()
{
    string  stxt = "The shadows which lie on the wall do not respond"
                 + " to light or movement of any kind. It seems clear"
                 + " that they are not the product of anything natural.";

    if (TP->query_skill(SS_AWARENESS) > 44)
    {
        stxt += " Covered deep in shadow, you notice some runes which"
              + " have been cunningly carved into the surface of the"
              + " wall.";
    }
    if (opening)
    {
        stxt += passage_text;
    }

    return BSN(stxt);
}

int
rasp_password(string str)
{
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (!IS_MORGUL_MAGE(TP))
        return 0;

    if (str != "echannon")
        return 0;

    write(BSN("Feeling a sudden sense of power flowing through your"
      + " undead veins, you rasp: Echannon!"));
    say(QCTNAME(TP) + " stands suddenly erect, and rasps some low"
      + " gutteral sounds in a commanding voice.\n");
    TP->add_mana(-30);

    if (opening)
    {
        write(BSN("Your words echo dimly in the already opened"
          + " passageway which leads through the dark stone wall."));

        return 1;
    }

    log_file("morgulmage_secret_entrance", ctime(time()) + " " 
        + capitalize(TP->query_real_name()) + " opened the passageway.\n", 0);
        
    set_alarm(3.0, 0.0, "open_wall");
    return 1;
}

int
read_runes(string str)
{
    if (!strlen(str))
        return 0;

    if (TP->query_skill(SS_AWARENESS) < 45)
        return 0;

    if (str != "rune" || str != "runes")
        return 0;

    exa_runes();
    return 1;
}

int
block_passageway()
{
    if (!IS_MORGUL_MAGE(TP))
    {
        write("As you begin to move forward, you become aware"
          + " of a terrifying power surrounding and controlling the"
          + " passageway. Your fists clench and your feet falter,"
          + " unwilling to do your bidding.\n");

        return 1;
    }
    
    return 0;
}