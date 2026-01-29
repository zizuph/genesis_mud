/*
 * tattoo.c
 *
 * The tattoo object that supports a more dynamic tattoo system.
 * Multiple tattoos on multiple sublocs are provided in a single object,
 * the tattoos have 2 adjectives which are selected by the player when
 * ordered, and may be placed in any one of 32 available locations. In
 * addition, when armour is worn over a tattoo, the tattoo is hidden from
 * view.
 *
 * Coder : Stexx
 * 
 * History : This is a revision of an earlier version, which transfers
 *           more of the code into the object itself to minimize chance
 *           of crashing the shadow.
 *           May 6/1995
 *
 *           Added the function there_can_be_only_one() to make sure that
 *           doubles of this tattoo never occur in a player's inventory,
 *           and that the latest tattoo is the only one to remain.
 *           Khail - Feb 23/96
 */

inherit "/std/object";

#pragma strict_types
#pragma save_binary
#include "tattoo_defines.h"

#include <wa_types.h>        //Needed for armour slot identification
#include <stdproperties.h>
#include "/d/Immortal/std/domain.h"  //Useful defines

#define MASTER_TATTOO "/d/Calia/gelan/tattoos/master_tattoo"

/* Global Vars */
mixed *tattoo_vars;  //Contains an array of variables used in creating the
                     //actual tattoo descriptions
string *g_sublocs;    //Global sublocs array
int view_tattoos = 1;   // Toggles player's ability to see his/her tattoos

/* Prototypes */
void create_object();
void init();
int tdisplay(string arg);        //The 'tdisplay' emote
mixed *find_tattoo(string str);  //Finding tattoos based on full location
varargs string find_armour(string str, object who);
string show_subloc(string subloc, object who, object for_obj);
void update_tattoos();
int add_tattoo(string adj1, string adj2, int design, string location);
int remove_tattoo(string location);
mixed *query_tattoos();
string *query_tat_sublocs();
void clean_out_tattoos();

/* Here starts the actual code */
/*
 * create_object();
 *
 * creates the initial tattoo object
 *
 */
void
create_object()
{
    ::create_object();
    tattoo_vars = (({}));
    set_name("_stexxs_tattoo_object");
    add_name("t_obj");
    set_short("tattoo object");
    set_long("tattoo object, should be invisible\n");
    remove_prop(OBJ_I_WEIGHT);    //Tattoo is massless
    remove_prop(OBJ_I_VOLUME);   //Tattoo has no volume
    remove_prop(OBJ_I_VALUE);    //Not worth anything
    add_prop(OBJ_M_NO_DROP, 1);    //Can't drop a tattoo
    add_prop(OBJ_M_NO_GIVE, 1);    //Can't give it away, either
    set_no_show();                 //Object not seen, only the sublocs
}

/*
 * Function Name : query_auto_load
 * Description : Makes the tattoo object an autoloader
 */
string
query_auto_load()
{
    return MASTER + ":";
}

/*
 * find_tattoo_objects
 * Description: Identifies all other tattoo objects in a player's inventory
 *              besides the one which is executing this function.
 * Arguments:   object ob - the object to test
 * Returns:     1 - test object is another tattoo object
 *              0 - test object not a tattoo object or is this object.
 */
int
find_tattoo_objects(object ob)
{
    if (MASTER_OB(ob) == MASTER_OB(TO) && TO != ob)
        return 1;
    else
        return 0;
}

/*
 * there_can_be_only_one
 *
 * Description: This function is called from update_tattoos, for the purpose
 *              of purging old tattoo objects from a player's inventory.
 *              This should never happen, but a recent bug has made this
 *              necessary, and should prevent a recurrence if a similar
 *              bug occurs in the future.
 */
void
there_can_be_only_one()
{
    object *inven;

    inven = all_inventory(environment(TO));

    inven = filter(inven, find_tattoo_objects);

    if (sizeof(inven))
        inven->remove_object();
}


/*
 * init();
 *
 * initializes some stuff when moved into the inventory of another object.
 * Here we use add_action to support the tdisplay emote.
 *
 */
void
init()
{
    ::init();

    FIXEUID;


  /* Want players to be able to 'tdisplay tattoo on location', so we call*/
  /* tdisplay(string str) when the player types the command this way. */
    add_action("tdisplay", "tdisplay"); 
    add_action("trub", "trub");
    add_action("tview", "tview");

  /*If any data is available for existing tattoos, load it.*/
    restore_object(TATTOO_SAVE);

    update_tattoos();
}


/*
 * Function name: tview
 * Description: toggles on/off being able to see your tattoos.
 */
int
tview()
{
    if (view_tattoos)
    {
        TP->catch_msg("You decide to no longer see all your tattoos.\n");
        view_tattoos = 0;
    }
    else
    {
        TP->catch_msg("You decide to see all your tattoos.\n");
        view_tattoos = 1;
    }

    return 1;
}

/*
 * tdisplay(string str);
 *
 * A simple 'emote' that goes with the tattoo.
 *
 */
int
tdisplay(string str)
{
    mixed *args;
    int i, design;
    string *temp, *strarr, adj1, adj2, location, arm, design_str;

    temp = MASTER_TATTOO->query_location_names();

    NF("Tdisplay what? Tdisplay tattoo on <location> maybe?\n");

    if (!strlen(str))
        return 0;

    if (member_array(str, temp) < 0)
    {
        /*Break up the string str into componets */
        /*and store as elements in array strarr */
        strarr = explode(str, " ");

        if (!sizeof(strarr) || strarr[0] != "tattoo")
            return 0;

        if (sizeof(strarr) == 1 || strarr[1] != "on")
        {
            NF("Tdisplay tattoo where? Tdisplay tattoo on <location> "+
                "maybe?\n");
            return 0;
        }

        if (sizeof(strarr) < 3)
        {
            NF("Tdisplay tattoo on what? Tdisplay tattoo on <location> " +
                "maybe?\n");
            return 0;
        }

        strarr = strarr[2..];     /*Don't need first 2 elements anymore*/

        if (sizeof(strarr))
            str = implode(strarr, " ");  /*Reassemble elements of strarr */
                                   /*into a single string which should */
                                 /*contain only the location of the tattoo */

        if (!strlen(str))
        {
            NF("Tdisplay tattoo on what?\n");
            return 0;
        }
    }
  
  /* Make sure the specified location is a possible tattoo location */
    if (member_array(str, temp) < 0)
    {
        NF("You don't have a tattoo on your "+str+" to display.\n");
        return 0;
    }

    args = find_tattoo(str);  /*Find the tattoo on specified location */

  /* If the location does exist, make sure that there's a tattoo there */
    if (!strlen(args[0]) || !strlen(args[1]))
    {
        NF("You don't have a tattoo on your " + str + " to display.\n");
        return 0;
    }

  /* This is what to do if tattoo is present and uncovered by armour */
    if (sizeof(args) == 4)
    {
        adj1 = (string)args[0];
        adj2 = (string)args[1];
        design = (int)args[2];
        design_str = MASTER_TATTOO->make_design(design, adj1, adj2);
        TP->catch_msg("You proudly display " + design_str + " by "+
            "giving everyone a better view of your " + str + ".\n");
        say(QCTNAME(TP) + " proudly displays " + design_str + " by giving " +
            "everyone a better view of " + TPQP + " " + str + ".\n");
        return 1;
    }
  
  /* This is what to do if the tattoo is present and covered by armour */
    if(sizeof(args) == 5)
    {
        adj1 = (string)args[0];
        adj2 = (string)args[1];
        design = (int)args[2];
        design_str = MASTER_TATTOO->make_design(design, adj1, adj2);
        location = (string)args[3];
        arm = (string)args[4];
        TP->catch_msg("You briefly remove your " + arm + ", proudly " +
            "displaying " + design_str + " on your " + str + ".\n");
        say(QCTNAME(TP) + " briefly removes " + TPQP + " " + arm + 
            ", proudly " + "displaying " + design_str + " on " + TPQP +
            " "+str+".\n");
        return 1;
    }

  return 0;
}

/*
 * Function name: trub
 * Description: Another emote
 */
int
trub(string str)
{
    mixed *args;
    int i, design;
    string *temp, *strarr, adj1, adj2, location, arm, design_str;

    temp = MASTER_TATTOO->query_location_names();
  
    NF("Trub what? Trub tattoo on <location> maybe?\n");

    if (!strlen(str))
        return 0;

    if (member_array(str, temp) < 0)
    {
        strarr = explode(str, " ");  
  /*Break up the string str into componets */
                                 /*and store as elements in array strarr */

        if (!sizeof(strarr) || strarr[0] != "tattoo")
            return 0;

        if (sizeof(strarr) == 1 || strarr[1] != "on")
        {
            NF("Trub tattoo where? Trub tattoo on <location> maybe?\n");
            return 0;
        }

        if (sizeof(strarr) < 3)
        {
            NF("Trub tattoo on what? Trub tattoo on <location> maybe?\n");
            return 0;
        }

        strarr = strarr[2..];     /*Don't need first 2 elements anymore*/

        if (sizeof(strarr))
            str = implode(strarr, " ");  /*Reassemble elements of strarr */
                                   /*into a single string which should */
                                 /*contain only the location of the tattoo */

        if (!strlen(str))
        {
            NF("Trub tattoo on what?\n");
            return 0;
        }
    }
  
  /* Make sure the specified location is a possible tattoo location */
    if(member_array(str, temp) < 0)
    {
        NF("You don't have a tattoo on your "+str+" to rub.\n");
        return 0;
    }

    args = find_tattoo(str);  /*Find the tattoo on specified location */

  /* If the location does exist, make sure that there's a tattoo there */
    if (!strlen(args[0]) || !strlen(args[1]))
    {
        NF("You don't have a tattoo on your " + str + " to rub.\n");
        return 0;
    }

  /* This is what to do if tattoo is present and uncovered by armour */
    if(sizeof(args) == 4)
    {
        adj1 = (string)args[0];
        adj2 = (string)args[1];
        design = (int)args[2];
        design_str = MASTER_TATTOO->make_design(design, adj1, adj2);
        TP->catch_msg("You thoughtfully rub " + design_str + " that adorns "+
            "your "+str+".\n");
        say(QCTNAME(TP) + " thoughtfully rubs " + design_str +
            " that adorns " + TPQP + " " + str + ".\n");
        return 1;
    }
  
  /* This is what to do if the tattoo is present and covered by armour */
    if (sizeof(args) == 5)
    {
        arm = (string)args[4];
        TP->catch_msg("You thoughtfully rub your "+arm+", thinking of the "+
            "tattoo beneath.\n");
        say(QCTNAME(TP)+" thoughtfully rubs "+TPQP+" "+arm+", perhaps "+
            "thinking of something concealed beneath it.\n");
        return 1;
    }
  return 0;
}


/*
 * find_tattoo(string str);
 *
 * This function takes a variable 'str' which is the name of a tattoo
 * location, i.e. left bicep, and finds the corresponding tattoo variables,
 * including the name of any armour worn over it in the form of an array.
 *
 */
mixed
*find_tattoo(string str)
{
    int i, design;
    string arm, adj1, adj2, location;
    mixed *temp;

  /* Find the corresponding abbreviation for the given location */
    location = MASTER_TATTOO->query_location_abbreviation(str);

  /* Load data for the tattoo on the given location */
    for (i = 0; i < sizeof(tattoo_vars); i++)
    {
        if(tattoo_vars[i][3] == location)
        {
            adj1 = tattoo_vars[i][0];
            adj2 = tattoo_vars[i][1];
            design = tattoo_vars[i][2];
            break;
        }
    }
  
  /* Find armour, if any, worn over the given location */
    arm = find_armour(location);

    if (strlen(arm))
        return ({adj1, adj2, design, location, arm });
    else
        return ({adj1, adj2, design, location });
}

/*
  * Function Name : find_armour
 * Description : Finds armour shorts in a location
 * Arguments : string str - abbreviated location of tattoo
 * Returns : the shorts of armours covering specified location
 */
varargs string
find_armour(string str, object who)
{
    int i;
    string temp;
  
    if (!who)
        who = environment();

  /*Check to see if multiple armour slots cover location*/
    temp = MASTER_TATTOO->query_armours(str, who);
  
    return temp;
}

 /* Here starts the code that was in the original shadow */

/*
 * Function Name : show_subloc
 *
 * Description : Called to see what's 'in' a subloc
 *
 * Arguments : string subloc  - The sublocation being examined
 *             object who     - The object containing the subloc
 *             object for_obj - The object examining the subloc
 *
 * Returns : The description of the subloc
 */
string
show_subloc(string subloc, object who, object for_obj)
{
    string str, adj1, adj2, location, loc_name, design_str;
    mixed tmp;
    int index, des_number;
  
  /*Is the subloc one from this object? If not, keep threading*/
  
    index = member_array(subloc, g_sublocs);
    if (index < 0)
        return environment()->show_subloc(subloc, who, for_obj);

  /* Subloc will not appear in an inventory check */
    if  (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

  /* If players look at themselves and have decided not to see all their */
  /* tattoos, don't show anything. */
    if (for_obj == who && !view_tattoos)
        return "";

    adj1 = tattoo_vars[index][0];          /*First adjective*/
    adj2 = tattoo_vars[index][1];          /*Second adjective*/
    des_number = tattoo_vars[index][2];    /*Design number*/
    design_str = MASTER_TATTOO->make_design(des_number, adj1, adj2);
    location = tattoo_vars[index][3];      /*Tattoo location (abbrev.)*/
    loc_name = MASTER_TATTOO->query_location_names(location);

    if (MASTER_TATTOO->query_sensitive_location(location))
        if (who != for_obj)
            return "";

  /* Is armour covering the location? If so, no subloc appears*/
    if (strlen(find_armour(location)))
        if (who != for_obj)
            return "";

    if (!random(2))
    {
        str = capitalize(design_str);

        if (for_obj == who)
        {
            str += " adorns your " + loc_name + ".";
            if (MASTER_TATTOO->query_sensitive_location(location))
                str += " (Concealed for decency)";
            else if (strlen(find_armour(location)))
                str += " (Concealed by armour)";
        }
        else
            str += " adorns "+who->query_possessive()+" "+loc_name+".";

        str += "\n";
        return str;
    }

    else if (!random(2))
    {
        if (for_obj == who)
            str = capitalize("Your ");
        else
            str = capitalize(who->query_possessive() + " ");

        str += loc_name + " is decorated with " + design_str + ".";

        if (who == for_obj)
        {
            if (MASTER_TATTOO->query_sensitive_location(location))
                str += " (Concealed for decency)";
            else if (strlen(find_armour(location)))
                str += " (Concealed by armour)";
        }
        str += "\n";
        return str;
    }

    if (for_obj == who)
        str = "You have ";
    else
        str = capitalize(who->query_pronoun()) + " has ";

    str += design_str;

    if (for_obj == who)
    {
        str += " on your " + loc_name + ".";
        if (MASTER_TATTOO->query_sensitive_location(location))
            str += " (Concealed for decency)";
        else if (strlen(find_armour(location)))
            str += " (Concealed by armour)";
    }
    else
        str += " on "+who->query_possessive()+" "+loc_name+".";

    str += "\n";
    return str;
}

/*
 * Function Name : update_tattoos
 *
 * Description : Refreshes all tattoo sublocs, and re-defines g_sublocs
 *               array based upon current tattoo_vars array
 *               Also executes there_can_be_only_one, which purges any
 *               tattoo objects which exist in the player's inventory
 *               besides this one, for whatever reason.
 */
void
update_tattoos()
{
    int i, des_number;
    string adj1, adj2, location;

  /* Remove old tattoo objects in the player's inv. */
    if (environment(TO) && interactive(environment(TO)))
        there_can_be_only_one();


  /* Clean out all the old sublocs */
    for (i = 0; i < sizeof(g_sublocs); i++)
    {
        environment()->remove_subloc(g_sublocs[i]);
    }

  /* Re-initialize g_sublocs variable */
    g_sublocs = (({}));

  /* Generate new g_sublocs array based on current tattoo_vars */
    for(i = 0; i < sizeof(tattoo_vars); i++)
    {
        adj1 = tattoo_vars[i][0];
        adj2 = tattoo_vars[i][1];
        des_number = tattoo_vars[i][2];
        location = tattoo_vars[i][3];
        environment()->add_subloc(SUBLOC+location, TO, location);
        g_sublocs += ({SUBLOC + location});
    }
}

/*
 * Function Name : add_tattoo
 *
 * Description : Adds a tattoo to a player. If successful, it adds the
 *               variables describing a specific design, writes it to file,
 *               and updates the players sublocs.
 *
 * Arguments : string adj1     - the first tattoo adjective
 *             string adj2     - the second tattoo adjective
 *             design          - tattoo design index
 *             string location - location of the tattoo
 *    NOTE: adj1 & adj2 must be in the TATTOO_ADJ array.
 *          design must be a valid index in the TATTOO_DESIGN array.
 *          location must be an abbreviated location as outlined in the
 *          TATTOO_COVER array, all of which are defined in tattoo.h
 *
 * Returns : 1 - Success
 *           0 - The specified location already has a tattoo
 *          -1 - Player already has maximum number of tattoos, as set by
 *               TATTOO_MAX_NUMBER in tattoo.h
 *          -2 - The first adjective is invalid.
 *          -3 - The second adjective is invalid.
 *          -4 - The design index is invalid.
 *          -5 - The tattoo location is invalid.
 * History: Nov 7/95 - Removed the valid adjective checks to allow spouse
 *                     tattoos. - Khail
 */
int
add_tattoo(string adj1, string adj2, int design, string location)
{

    FIXEUID;

  /* Does a tattoo exist in that location? */
    if (member_array(SUBLOC+location, g_sublocs) != -1)
        return 0;

  /* Is the player allowed to get another tattoo? */
    if (sizeof(g_sublocs) >= TATTOO_MAX_NUMBER)
        return -1;

  /* Is first adjective valid? */
  /*
    if (MASTER_TATTOO->query_tattoo_adjs(adj1) < 0)
        return -2;
   */

  /* Is second adjective valid? */
  /*
    if (MASTER_TATTOO->query_tattoo_adjs(adj2) < 0)
        return -3;
   */

  /* Is design number valid? */
    if (!MASTER_TATTOO->query_tattoo_design(design))
        return -4;

  /* Is the location valid? */
    if (sizeof(MASTER_TATTOO->query_location_name(location)))
        return -5;

    tattoo_vars += ({ ({ adj1, adj2, design, location }) });
    g_sublocs += ({SUBLOC + location});
    save_object(TATTOO_SAVE);

    update_tattoos();

    return 1;
}

/*
 * Function Name : remove_tattoo
 *
 * Description : Removes a tattoo from a player. If the provided location
 *               is found in tattoo_vars, it is removed from tattoo_vars,
 *               the object variables are saved, and the player's sublocs
 *               are updated.
 *
 * Arguments : string location - Location of the tattoo to be removed, 
 *                               in abbreviated form as in TATTOO_COVER.
 *
 * Returns : 1 - Success.
 *          -1 - Failure, no tattoo in provided location.
 *          -2 - Unspecified failure.
 */
int
remove_tattoo(string location)
{
    int i, index;

  /* Is there a tattoo at the provided location? */
    if (member_array(SUBLOC+location,g_sublocs) < 0)
        return -1;

    for (i = 0; i < sizeof(tattoo_vars); i++)
    {
        if(location == tattoo_vars[i][3])
        {
            tattoo_vars -= ({tattoo_vars[i]});
            save_object(TATTOO_SAVE);
            if (!sizeof(tattoo_vars))
            {
                clean_out_tattoos();
                return 1;
            }
        update_tattoos();
        return 1;
        }
    }
    return -2;
}

/*
 * Function Name : query_tattoos
 *
 * Description : Returns the tattoo_vars array which contains all the 
 *               current tattoo settings.
 */
mixed
*query_tattoos()
{
      return tattoo_vars;
}

/*
 * Function Name : query_tat_sublocs
 *
 * Description : Gets all sublocs for existing tattoos.
 *
 * Returns : g_sublocs.
 */
string
*query_tat_sublocs()
{
    return g_sublocs;
}

/*
 * Function Name : clean_out_tattoos
 *
 * Description : Removes the tattoo object and the tattoo save file.
 */
void
clean_out_tattoos()
{
    FIXEUID;

    rm(TATTOO_SAVE+".o");
    remove_object();
}
