/* Dust 920812
 * This headerfile includes the skeleton for the colormaze with
 * spread hints. The hints are stored in a file HINTFILE.
 * The user-program has to set the following defines BEFORE
 * including this:
 * NORTH, SOUTH, EAST, WEST: pathnames to the 4 possible
 *	neighbour rooms
 * HINTINDEX: number 0..6. This is the index of the hint this
 *	rooms needs.
 * TWOHINTS: >0 if two hints are needed
 * HINT2INDEX: same as HINTINDEX for second room
 * The followig functions can be used:
 * make_new_path(): Creates a new random sequence and stores it in
 *	HINTFILE. No update made.
 * do_remove_exit(): Removes current exit from room (rarely used)
 * do_add_exit(): Adds current hint to room (rarely used)
 * set_hint(): Gets hint from file, removes old exit and adds
 *	the corresponding new one. An exit MUST already exist!
 * update_rooms(): Updates all rooms that need the new hint
 */


#define HINTFILE "/d/Terel/common/town/mansion/colors/colorpath.hint"
#define SHS ({ "n", "e", "s", "w" })
/* all HINTROOMS used for update in update_rooms() */
#define HINTROOMS ({	COLDIR + "blue", \
			COLDIR + "purple", \
			COLDIR + "green", \
			COLDIR + "orange", \
			COLDIR + "white", \
			COLDIR + "violet", \
			COLDIR + "col_96", \
			COLDIR + "col_98", \
			COLDIR + "col_85", \
			COLDIR + "col_87", \
			COLDIR + "col_89", \
			COLDIR + "col_74", \
			COLDIR + "col_76", \
			COLDIR + "col_78", \
			COLDIR + "col_63", \
			COLDIR + "col_65", \
			COLDIR + "col_67", \
			COLDIR + "col_54", \
			COLDIR + "col_56", \
			COLDIR + "col_43", \
			COLDIR + "col_45", \
			COLDIR + "col_34", \
			COLDIR + "col_23", \
			COLDIR + "col_25", \
			COLDIR + "col_14" })


string hint;
string hint2;

update_rooms()
{
    int i;
    object *hintrooms;
    object hroom;

    hintrooms = HINTROOMS;
    for (i=0; i<sizeof(hintrooms); i++)
    {
	hroom = find_object(hintrooms[i]);
	if (hroom) hroom->set_hint();
    }
}

void
make_new_path()
{
    int i;
    string s;

    s = "";
    for (i=0; i<6; i++) {
        s += SHS[random(4)];
    }
    rm(HINTFILE);
    write_file(HINTFILE, s + "\n");
/*
	write_bytes(HINTFILE, i, SHS[random(4)]);
 */
    update_rooms();
}

do_add_exit()
{
    string target, comm;

    if (hint != "0")
    {
	if (hint == "n") {target = NORTH; comm = "north";}
	if (hint == "e") {target = EAST;  comm = "east";}
	if (hint == "s") {target = SOUTH; comm = "south";}
	if (hint == "w") {target = WEST;  comm = "west";}
	add_exit(target, comm, 0);
    }
    if (!TWOHINTS) return;
    if (hint2 != "0")
    {
	if (hint2 == "n") {target = NORTH; comm = "north";}
	if (hint2 == "e") {target = EAST;  comm = "east";}
	if (hint2 == "s") {target = SOUTH; comm = "south";}
	if (hint2 == "w") {target = WEST;  comm = "west";}
	add_exit(target, comm, 0);
    }
}

void
do_remove_exit()
{
    if (hint != "0")
    {
	if (hint == "n") remove_exit("north");
	if (hint == "e") remove_exit("east");
	if (hint == "s") remove_exit("south");
	if (hint == "w") remove_exit("west");
    }
    if (!TWOHINTS) return;
    if (hint2 == "0") return;
    if (hint2 == "n") remove_exit("north");
    if (hint2 == "e") remove_exit("east");
    if (hint2 == "s") remove_exit("south");
    if (hint2 == "w") remove_exit("west");
}

void
set_hint()
{
    string temp;
    /* We first remove the "old" exit */
    do_remove_exit();
    /* Try to get the hint... if none, create hintfile and make path */
    hint = read_bytes(HINTFILE, HINTINDEX, 1);
    if (REVERSE)
    {
	if (FROM == hint)
	{
	    if (hint == "n") hint = "s";
	    else if (hint == "e") hint = "w";
	    else if (hint == "w") hint = "e";
	    else if (hint == "s") hint = "n";
	}
	else hint = "0";
    }
    if (TWOHINTS)
    {
	hint2 = read_bytes(HINTFILE, HINT2INDEX, 1);
	if (REVERSE)
	{
	    if (FROM2 == hint2)
	    {
		if (hint2 == "n") hint2 = "s";
		else if (hint2 == "e") hint2 = "w";
		else if (hint2 == "w") hint2 = "e";
		else if (hint2 == "s") hint2 = "n";
	    }
	    else hint2 = "0";
	}
    }
    /* Add the new exit */
    do_add_exit();
}


