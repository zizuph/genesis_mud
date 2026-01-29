#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <config.h>
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

int seal = 1;

public void
init()
{
    ::init();
    add_action("open_letter", "open");
    add_action("read_letter", "read");
    add_action("open_letter", "break");
}

void
create_object()
{
    set_name("letter");
    set_long("@@desc_letter");
    add_name("_berions_letter");
    add_prop(OBJ_I_WEIGHT, 20); /* 20 g */
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    setuid();
    seteuid(getuid());
}

string
desc_letter()
{
    string txt;

    txt = "It is a rather normal letter. The slight yellow " +
        "colour of the paper indicates it has been lying " +
        "untouched for a long time. The letter is folded " +
        "two times so you cannot see anything that is " +
        "written.";
    if (seal)
        txt+= " Right now the letter is sealed.\n";
    else
        txt+= " There are remains of a seal on the letter, but " +
            "the seal is broken and the letter is open.\n";
    txt+="On the letter is written: " +
        "\n\n         LABAL\n\n";

    return txt;

}

int
open_letter(string str)
{
    if ((str) && (str == "letter") || (str == "seal"))
    {
        write("You stick your finger under the seal and break it. " +
            "With a cracking sound the letter opens " +
            "and you can see the text. Alas, it is written " +
            "in an unknown language.\n");
        TP->add_prop("_broke_labals_seal", 1);
        say(QCTNAME(TP) + " breaks the seal on a letter in " +
            TP->query_possessive() + " hands with a ripping " +
            "sound.\n");
        seal = 0;
        return 1;
    }
    return 0;
}

int
read_letter(string str)
{
    if ((str) && (str == "letter"))
    {
        if (seal)
        {
            write("You can not read a sealed letter!\n");
            return 1;
        }
        write("You try to read the text in the letter but " +
            "of no use. It is written in a langauge you can not " +
            "understand a word of. The only thing you can make " +
            "out of it is the author as the name Berion can be " +
            "understood has signed it.\n");
        say(QCTNAME(TP) + " bends over the letter in " +
            TP->query_possessive() + " hands and tries to read it. " +
            "The look of " + TP->query_possessive() + " face tells " +
            "you there wasnt much of intrest in it.\n");
        return 1;
    }
    return 0;
}
 
int
query_seal()
{
    return seal;
}
