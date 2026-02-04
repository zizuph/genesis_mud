/*
 *    This is the include file to tent_0x.c files
 */
#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"
#define WIRE            TENT_DIR + "wire.c"
#define MANEGE          TENT_DIR + "manege.c"

#define NO_OF_DWARVES   2
#define NO_OF_HUMANS    2
#define NO_OF_HOBBITS   2
#define NO_OF_ELVES     2
#define HARD_TO_CLIMB   10

string check_wire();
string check_manege();
int climb_up();

string
check_wire()
{
    int i, j;
    object wire, *obs;
    string str, name, people;

    wire = find_object(WIRE);
    str = "No one is walking on the wire.";
    if (!wire) return str + "\n";
    people = "These are walking on the wire:";

    obs = all_inventory(wire);
    j = 0;
    for (i=0; i<sizeof(obs); i++) {
	if ( living(obs[i]) && !(obs[i]->query_invis()) ) {
	    j++;
	    name = obs[i]->query_art_name(TP);
	    if (j==1) people = people + " " + name;
	    if (j>1) people = people + ", " + name;
	}
    }
    if (j > 0) str = people + ".";
    str = BSN(str);
    return str;
}

string
check_manege()
{
    int i, j;
    object manege, *obs;
    string str, name, people;

    manege = find_object(MANEGE);
    str = "No one is standing on the manege.";
    if (!manege) return str + "\n";
    people = "These are standing on the manege:";

    obs = all_inventory(manege);
    j = 0;
    for (i=0; i<sizeof(obs); i++) {
	if ( living(obs[i]) && !(obs[i]->query_invis()) ) {
	    j++;
	    name = obs[i]->query_art_name(TP);
	    if (j==1) people = people + " " + name;
	    if (j>1) people = people + ", " + name;
	}
    }
    if (j > 0) str = people + ".";
    str = BSN(str);
    return str;
}

int
climb_up()
{
    int tp_climb;
    int drunk;

    drunk = TP -> query_intoxicated();

    if (TP -> query_wiz_level() > 0)
        return 0;

    tp_climb = (TP->query_skill(SS_CLIMB)) + random(4);
    if (tp_climb > HARD_TO_CLIMB && drunk >= 20) {
        write("Your conscience tells you alcohol and heights probably " +
           "dont mix well together and could only result in disaster. " +
           "But when have you ever listened to your conscience. " +
           "You climb up the mast easily.\n");
        return 0;
    }

    if (tp_climb  > HARD_TO_CLIMB) {
        write("You climb up the mast easily.\n");
        return 0;
    } else {
        write("You do not dare to go up in the mast.\n");
        say(QCTNAME(TP) + " decides to stay on the ground.\n");
        return 1;
    }
}
