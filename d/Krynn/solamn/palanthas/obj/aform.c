/* created by Aridor 09/17/93 */

/*
 *   this is the formular used in the palace.
 *   there is room for a name, a purpose, a seal, 3 slots for authorization.
 *
 *   after cloning you need to call set_form_type to give it a specific name.
 */

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
/*#include <config.h>
#include <cmdparse.h>*/
#define NUMBER_OF_PERMISSIONS 3

/* ftype is the title of the form
 * name is the name of the applicant
 * purpose is what the from is for
 * seal is the seal (=signature) of the applicant
 * *slot are slots for the seals, signatures, stamps, punches, labels of the
 *       offices, the max number of slots is determined by num_slots.
 */

string ftype;
string f_name;
string fpurpose;
object fseal;
string *fslot;
int fnum_slots;
 
void
create_object()
{
    set_name("form");
    set_adj("empty");
    set_short("empty form");
    set_long("It's a sheet of paper with readable words on it.\n");
    fnum_slots = NUMBER_OF_PERMISSIONS;
    fslot = allocate(fnum_slots);

    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 0); /* 0 copper */
    /*::create_object(); --needed?*/
}


init()
{
    add_action("write_something","write");
    add_action("stick_on","put");
    add_action("stick_on","stick");
    add_action("write_something","fill");
    add_action("read_form","read");
    ::init();
}



string
return_slots()
{
    string str = "";
    int i;
    for (i = 0; i < sizeof(fslot); i++)
      str += "     " + (fslot[i] ? fslot[i] : ".................") + "\n";
    return str;
}


string
write_contents()
{
    string permits = return_slots();
    return "The form has these lines written on it:\n\n"
        + "     " + (ftype ? capitalize(ftype) : "..........") + " Form\n\n"
        + "Hereby I, " + (f_name ? capitalize(f_name) : ".........")
        + ", apply for\n"
        + (fpurpose ? fpurpose : ".....................................")
        + ".\n" + "     Seal: "
        + (fseal ? (fseal->query_short()) : ".........") + "\n\n"
        + "Permissions given:\n"
        + permits;
}


int
read_form(string str)
{
    int succ;
    string dummy;
    if (!str)
    {
        NF("Read what?\n");
        return 0;
    }
    succ = sscanf(str, "%s form", dummy);
    if (succ || str == "form")
    {
	if (!present(TO,TP))
	{
	    NF("You are not carrying a form.\n");
	    return 0;
	}
        write(write_contents());
        return 1;
    }
    NF("Read what?\n");
    return 0;
}



/*just in case you need it:*/
void
set_form_num_slots(int fnum)
{
    fnum_slots = fnum;
    fslot = allocate(fnum);
}

int query_form_num_slots() { return fnum_slots; }


int
set_form_type(string what_type)
{
    seteuid(getuid(this_object()));
    if (ftype)
    {
        write("The type has already been filled in!\n");
        return 0;
    }
    ftype = what_type;
    this_object()->remove_adj(this_object()->query_adj());
    this_object()->set_adj(what_type);
    this_object()->set_short(what_type + " form");
    return 1;
}


string
query_form_type()
{
    return ftype;
}


int
set_form_name(string fthe_name)
{
    if (f_name)
    {
        write("The name has already been filled in!\n");
        return 0;
    }
    f_name = fthe_name;
    return 1;
}

string query_form_name() { return f_name; }


int
set_form_purpose(string the_purpose)
{
    if (fpurpose)
    {
        write("The purpose has already been filled in!\n");
        return 0;
    }
    fpurpose = the_purpose;
    return 1;
}

string query_form_purpose() { return fpurpose; }


int
set_form_seal(object the_seal)
{
    if (fseal)
    {
        write("There is already a seal there!\n");
        return 0;
    }
    fseal = the_seal;
    return 1;
}

object query_form_seal() { return fseal; }


/* set_slot sets the first empty slot (if found) to the_slot 
 * return 1 if successful, 0 if failure
 */
int
set_form_slot(string the_slot)
{
    int i = 0;
    while (i < sizeof(fslot) && i < fnum_slots && fslot[i])
      i++;
    if (i == fnum_slots)
    {
        write("I'm sorry, there is no more room for permissions!\n");
        return 0;
    }
    fslot[i] = the_slot;
    return 1;
}

string query_form_slot(int which) { return fslot[which]; }

string * query_form_slots() { return fslot; }


/* NO clear/erase functions! Stuff that is written stays....:-)*/




object
check_pen()
{
    NF("How can you write without a pen?\n");
    return present("pen", TP);
}


int
write_something(string str)
{
    string the_entry;
    int succ;
    seteuid(getuid(TO));

    /* must carry the form to be able to fill it in */
    if (!present(TO,TP))
      {
	NF("You are not carrying a" + ((short(TO)[0..0] == "a" ||
				       short(TO)[0..0] == "e" ||
				       short(TO)[0..0] == "i" ||
				       short(TO)[0..0] == "o" ||
				       short(TO)[0..0] == "u") ? "n " : " ")
				       + short(TO) + ".\n");
	return 0;
      }
    /* no string at all? Sheesh...:) */
    if (!str)
    {
	NF(capitalize(query_verb()) + " <where> <what>? - You can make out " +
	   "the following 'where's on the form: type, name, purpose, " +
	   "signature, permission.\n");
	return 0;
    }
    /* write the name */
    succ = sscanf(str, "name %s", the_entry);
    if (succ)
    {
        if (!check_pen()) return 0;
        if (!set_form_name(lower_case(the_entry))) return 1;
        write("You fill in the name " + capitalize(the_entry) 
           +  " on the form.\n");
        say(QCTNAME(TP) + " writes something on a sheet of paper.\n");
        return 1;
    }
    /* write the purpose */
    succ = sscanf(str, "purpose %s", the_entry);
    if (succ)
    {
        if (!check_pen()) return 0;
        if (!set_form_purpose(the_entry)) return 1;
        write("You fill in the purpose of the form.\n");
        say(QCTNAME(TP) + " writes something on a sheet of paper.\n");
        return 1;
    }
    /* write the signature NOT ALLOWED ANYMORE*/
    succ = sscanf(str,"seal %s", the_entry);
    if (succ)
    {
	/* if (!check_pen()) return 0;
	   if (!set_form_seal(the_entry)) return 1;
	   write("You sign the form with " + the_entry + "\n");
	   say(QCTNAME(TP) + " writes something on a sheet of paper.\n");*/
	
        write("I wonder how you write a seal? Maybe you should try "
	      + "to stick one on the form?\n");
        return 1;
    }
    /* don't write the permissions */
    succ = sscanf(str,"permit %s", the_entry);
    if (!succ)
      succ = sscanf(str,"permission %s", the_entry);
    if (succ)
    {
        write("Hmmm, you get the distinct feeling your permission would "
	      +  "not interest anybody in the least. Maybe you should "
	      +  "persuade someone else to give the permissions to you?\n");
        return 1;
    }
    /* don't write the type */
    succ = sscanf(str,"type %s", the_entry);
    if (succ)
    {   
        if (!check_pen()) return 0;
        write("You write the type of the form.\n");
        say(QCTNAME(TP) + " writes something on a sheet of paper.\n");
        set_form_type(lower_case(the_entry));
        return 1;
    }
    /* not found anything to write??*/
    NF(capitalize(query_verb()) + " <where> <what>? - You can make out the " +
       "following 'where's on the form: type, name, purpose, seal, " +
       "permission.\n");
    return 0;
}



int
stick_on(string str)
{
    string the_entry;
    int succ;
    object what;
    seteuid(getuid(TO));

    /* no str defined? */
    if (!str)
    {
        NF(capitalize(query_verb()) + " what on what?\n");
        return 0;
    }
    /* put the seal on the form */
    succ = sscanf(str, "%s on form", the_entry);
    if (!succ)
      succ = sscanf(str, "%s on the form", the_entry);
    if (succ)
    {
        what = present(the_entry, TP);
        if (!what || !what->query_short())
        {
            write("How can you " + query_verb() + " something on the "
		  +  "form if you don't have it?\n");
            return 1;
        }
        if ((what->query_prop(OBJ_I_VOLUME) > 4)             ||
            (what->query_prop(OBJ_I_WEIGHT) > 2)             ||
            what->query_prop(OBJ_M_NO_DROP)                  ||
            what->query_prop(OBJ_M_NO_GIVE)                  ||
            (what->query_prop(OBJ_I_VALUE) > 1))
        {
            write("The " + what->query_short() + " cannot be put there.\n");
            return 1;
        }
        if (!set_form_seal(what)) return 1;
        write("You " + query_verb() + " " + (what->query_short())
	      + " on the form.\n");
        /*what->remove_object();
	  NO! only remove from the inventory. Actually it should is:*/
	what->move(TO,1);
        say(QCTNAME(TP) + " " + query_verb() +"s something on a sheet of "
	    + "paper.\n");
        return 1;
    }
    NF(capitalize(query_verb()) + " what on what?\n");
    return 0;
}

void
leave_inv(object ob, object dest)
{
    if (ob->id("seal"))
      fseal = 0;
    ::leave_inv(ob,dest);
}
