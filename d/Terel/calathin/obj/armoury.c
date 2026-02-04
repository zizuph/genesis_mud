
#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
    set_short("armoury shack");
    set_long("This shack is used to hold all the weapons and armours "+
                   "used in Tournaments and for practice on the field."+
                   "Racks line the walls and have a variety of weapons and "+
                   "armours for use. Each weapon type has it's own selection "+
                   "to be found. Just choose <item> to take one.\n");
    add_item(({"sword","swords"}), "There are a few different swords. "+
                   "Longsword, shortsword, and two-handed sword.\n");
    add_item(({"polearms","polearm"}), "There are a few different polearms. "+
                   "Halberd, spear, and quarterstaff.\n");
    add_item(({"axe","axes"}), "There are  two different axes. "+
                   "Battle axe and hand axe.\n");
    add_item(({"dagger","daggers"}), "There are two different daggers. "+
                   "Stiletto and dagger.\n");
    add_item(({"weapon","weapons"}), "There are various weapons on the wall. "+
                   "Examine them by type.\n");
    add_item(({"armour","armours"}), "There is an armour for each body "+
                   "location. Greaves, bracers, chainmail, shield, and helm.\n");
    add_cmd_item("longsword", "choose", "@@longsword");
    add_cmd_item("shortsword","choose","@@shortsword");
    add_cmd_item("two-handed sword","choose","@@two_hand");
    add_cmd_item("halberd","choose","@@halberd");
    add_cmd_item("quarterstaff","choose","@@staff");
    add_cmd_item("spear","choose","@@spear");
    add_cmd_item("stiletto","choose","@@stiletto");
    add_cmd_item("dagger","choose","@@dagger");
    add_cmd_item("battle axe","choose","@@battle");
    add_cmd_item("hand axe","choose","@@hand");
    add_cmd_item("greaves","choose","@@greaves");
    add_cmd_item("bracers","choose","@@bracers");
    add_cmd_item("chainmail","choose","@@chainmail");
    add_cmd_item("helm","choose","@@helm");
    add_cmd_item("shield","choose","@@shield");

}


int
longsword()
{
    object longsword;

    longsword = clone_object(CALATHIN_DIR + "weapon/longsword");
    longsword->add_name("_arena_");
    longsword->move(TP);
    write("You choose a longsword from the wall.\n");
    say(" chooses a longsword from the wall.\n");
    return 1;
}

int
shortsword()
{
    object shortsword;

    shortsword = clone_object(CALATHIN_DIR + "weapon/shortsword");
    shortsword->add_name("_arena_");
    shortsword->move(TP);
    write("You choose a shortsword from the wall.\n");
    say(" chooses a shortsword from the wall.\n");
    return 1;
}

int
two_hand()
{
    object two_handed;

    two_handed = clone_object(CALATHIN_DIR + "weapon/twohand");
    two_handed->add_name("_arena_");
    two_handed->move(TP);
    write("You choose a two-handed sword from the wall.\n");
    say(" chooses a two-handed sword from the wall.\n");
    return 1;
}

int
battleaxe()
{
    object battleaxe;

    battleaxe = clone_object(CALATHIN_DIR + "weapon/battleaxe");
    battleaxe->add_name("_arena_");
    battleaxe->move(TP);
    write("You choose a battleaxe from the wall.\n");
    say(" chooses a battleaxe from the wall.\n");
    return 1;
}

int
handaxe()
{
    object handaxe;

    handaxe = clone_object(CALATHIN_DIR + "weapon/handaxe");
    handaxe->add_name("_arena_");
    handaxe->move(TP);
    write("You choose a handaxe from the wall.\n");
    say(" chooses a handaxe from the wall.\n");
    return 1;
}

int
halberd()
{
    object halberd;

    halberd = clone_object(CALATHIN_DIR + "weapon/halberd");
    halberd->add_name("_arena_");
    halberd->move(TP);
    write("You choose a halberd from the wall.\n");
    say(" chooses a halberd from the wall.\n");
    return 1;
}

int
spear()
{
    object spear;

    spear = clone_object(CALATHIN_DIR + "weapon/spear");
    spear->add_name("_arena_");
    spear->move(TP);
    write("You choose a spear from the wall.\n");
    say(" chooses a spear from the wall.\n");
    return 1;
}

int
staff()
{
    object staff;

    staff = clone_object(CALATHIN_DIR + "weapon/staff");
    staff->add_name("_arena_");
    staff->move(TP);
    write("You choose a staff from the wall.\n");
    say(" chooses a staff from the wall.\n");
    return 1;
}

int
stiletto()
{
    object stiletto;

    stiletto = clone_object(CALATHIN_DIR + "weapon/stiletto");
    stiletto->add_name("_arena_");
    stiletto->move(TP);
    write("You choose a stiletto from the wall.\n");
    say(" chooses a stiletto from the wall.\n");
    return 1;
}

int
dagger()
{
    object dagger;

    dagger = clone_object(CALATHIN_DIR + "weapon/dagger");
    dagger->add_name("_arena_");
    dagger->move(TP);
    write("You choose a dagger from the wall.\n");
    say(" chooses a dagger from the wall.\n");
    return 1;
}

int
greaves()
{
    object greaves;

    greaves = clone_object(CALATHIN_DIR + "armour/steel_greaves");
    greaves->add_name("_arena_");
    greaves->move(TP);
    write("You choose a pair of greaves from the wall.\n");
    say(" chooses a pair of greaves from the wall.\n");
    return 1;
}

int
bracers()
{
    object bracers;

    bracers = clone_object(CALATHIN_DIR + "armour/steel_bracers");
    bracers->add_name("_arena_");
    bracers->move(TP);
    write("You choose a pair of bracers from the wall.\n");
    say(" chooses a pair of bracers from the wall.\n");
    return 1;
}

int
chainmail()
{
    object chainmail;

    chainmail = clone_object(CALATHIN_DIR + "armour/steel_chainmail");
    chainmail->add_name("_arena_");
    chainmail->move(TP);
    write("You choose a chainmail from the wall.\n");
    say(" chooses a chainmail from the wall.\n");
    return 1;
}

int
shield()
{
    object shield;

    shield = clone_object(CALATHIN_DIR + "armour/steel_shield");
    shield->add_name("_arena_");
    shield->move(TP);
    write("You choose a shield from the wall.\n");
    say(" chooses a shield from the wall.\n");
    return 1;
}

int
helm()
{
    object helm;

    helm = clone_object(CALATHIN_DIR + "armour/steel_helm");
    helm->add_name("_arena_");
    helm->move(TP);
    write("You choose a helm from the wall.\n");
    say(" chooses a helm from the wall.\n");
    return 1;
}





