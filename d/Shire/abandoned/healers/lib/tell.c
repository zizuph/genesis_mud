/*  -*- LPC -*-  */
/*
 * Function name:   tellem
 * Arguments:	    subjective	(object)
 *			The object which is the subject of the action.
 *		    objective	(object)
 *			The object which is the object of the action.
 *		    text	(string)
 *			The special tellem format.
 *		    tell_all	(int)
 *			0 [default] : Tell only those who see fights.
 *			1	    : Tell all in this room.
 * Description:
 *	This routine is special, since it includes outputing of text
 *	to involved parties in one special tellem format. This format
 *	is specified below.
 */


/*

NAME
	tellem format	- The format used in the tellem style.

SYNOPSIS
	Information only to use with the tellem functions.

DESCRIPTION
	The tellem format is used to simply produce text in a standard
	fashion in a simple way. The format is supposed to be as flexible
	as possible, being fast and versatile.

	To understand it it is needed to know that the tellem format is
	just a formalazition of the usual write/say routines which use
	macros like QCTNAME and etc.

	It is used to print out messages of actions taking place. If
	someone does an action, it is the 'subject' of the action. If
	this subject does something with another living, this living
	is the 'direct object' or just the 'object' of the action.
	The relationship between these objects determine what form to
	write to the different parties.

	Lets take a simple example, I hit you:

	       -----			S : Subject of action.	  ($)
	       | W |			O : Object of action.	  (#)
	       -----			W : Watchers of action.

	-----	hit    -----
	| S |  ----->  | O |
	-----	       -----

	S gets: You hit (your name or nonmet description).
	O gets: Rogon hits you.
	W gets: Rogon hits (your name or nonmet description).

	The code will also deal with cases where the subject and the object
	of the action is the same living, called a 'reflexive action'. Let's
	say I hit myself:

	S gets: You hit yourself.
	W gets: Rogon hits himself.

SYNTAX
	In order to differenciate between special codes and pure text
	the following syntax is reserved:

	    $<letter>
	    #<letter>

	    {text}
	    {text1;text2}
	    {text1;text2;text3}

WARNING!!
	This routine is not as fast as macro functions using write()
	and say(), so unless you have good reason, you should *not*
	use this file.

PRONOUNS
	The gender is always defined as male, but if the subject, object is
	of another gender, it automatically gets right.

	Forms: $ (subject) or # (object).
	Letter:
	    N	- Name. 	    (Rogon/The white bearded dwarf/Someone)
	    N's - Possessive form:  (Rogon's/The white bearded dwarf's/Someone's)
	    S	- Subjective form:  (he/she/it)
	    O	- Objective form:   (him/her/it)
	    P	- Possessive form:  (his/her/its)
	    R   - Reflexive form    (himself/herself/itself)

	Uppercase letters will give uppercase first letter, while lowercase
	yields lowercase first letter.

VERBS
	For verbs to function a similar syntax is used:
	    $<verb>	- Subject does an action.
	    #<verb>	- Object does an action

	$N $chant a spell.

	    Galadriel gets: You chant a spell.
	    Rogon gets:	Galadriel chants a spell.	     (met)
			The garlanded elf chants a spell.    (nonmet)

	$N $is devastated by #n's spell.

	    Galadriel gets: Rogon is devastated by your spell.	      (met)
			    The odd dwarf is devastated by your spell.(nonmet)
	    Rogon gets:     You are devastated by Galadriel's spell.  (met)
			    You are devastated by the garlanded elf's spell.
								      (nonmet)

	#N #fumble with #p weapon.

	    Galadriel gets: Rogon fumbles with his weapon.		(met)
			    The odd dwarf fumbles with his weapon.	(nonmet)
	    Rogon gets:     You fumble with your weapon.


	$N $cry out in pain!

	    Galadriel gets: You cry out in pain!
	    Rogon gets:     Galadriel cries out in pain!		(met)
			    The garlanded elf cries out in pain!	(nonmet)

ALTERNATIVE FORMS
	{text1;text2;text3} is used to give

	    text1: to the subject
	    text2: to the object
	    text3: to other living objects.

	${text1;text2} is used to give

	    text1: to the subject
	    text2: to the object and other livings.

	#{text1;text2} is used to give

	    text1: to the subject and other livings.
	    text2: to the object

	${text} is used to give

	    text: to the subject only.

        #{text} is used to give
      
            text: to the object only.

	NOTE: You can use $ or # forms within a {} construct:

	    {You feel a terrible pain!;$N looks terribly hurt.}

	But you can not use {} within {}'s. (Why should you?)
       
        You *can* use $ and # within the text as usual.
        I.e.: $N $look at $p $'s.

EXAMPLES
	$N $hit #n nastily with $p battle hammer.
	#N #cry like a baby when seeing that #p hammer is lost.

IMPLEMENTATION
	The implementation uses the function replace_string and replace_strings
	from the file /d/Immortal/rogon/lib/strings.c to replace it with
	value by function calls defined in /d/Immortal/rogon/include/lib.h.
	These calls are executed mainly in /d/Immortal/rogon/lib/lib.c.

*/

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>
#include <options.h>
#include "defs.h"

#define BRACK "["
#define ENDBRACK "]"
#define BRACE "{"
#define DELIM ";"
#define ENDBRACE "}"

inherit STRING_FILE;

string
replace_braces(string str, object subj, object obj)
{
    int ind;
    string ret = "";
    string left;
    string part;
    string *p = ({ "", "", "" });

    ind = index(str, BRACE);
    if (ind == -1)
	return str;

    left = str;

    while (ind != -1)
    {
	if (ind > 0)
	    ret += str_to(left, ind);

	left = str_from(left, ind);
	ind = index(left, ENDBRACE);
	part = str_to(left, ind);

	if (sscanf(part, "%s"+DELIM+"%s"+DELIM+"%s", p[0], p[1], p[2])==3)
	    ret += V_ALT(p[0], p[1], p[2], subj, obj);
	else if (sscanf(part, "%s"+DELIM+"%s", p[0], p[1])==2)
	    ret += V_ALT(p[0], p[1], AS_OBJ, subj, obj);
	else
	    ret += V_FOR(subj, part);

	left = str_from(left, ind);
	ind  = index(left, BRACE);
    }
    return ret + left;
}

int is_char(int ch) 
{ 
    return (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || ch == '_'; 
}

#define DEBUG(x) /* find_player("rogon")->catch_msg("In replace_specs> " + x + "\n"); */

string
replace_specs(string str, object subj, object obj)
{
    int i=0, last_i, j, k, slen = strlen(str); 
    string ret = "", chr; 
    object for_obj;
    string *buf = explode(str, "");

    while (1)  // Infinite loop.
    {
	DEBUG("i = " + i)
        if (i >= slen)
            return ret;
        j = member_array("$", buf[i..slen]);
        k = member_array("#", buf[i..slen]);
        if (j == -1) j = k;
        if (k != -1) j = MIN(j,k);     // Finds j = MIN(j,k) unless j==-1 or k==-1.

        DEBUG("MAX = " + j)
        if (j == -1)
        {
            DEBUG("Returning: " + ret + str[i..-1] )
            return ret + str[i..-1];  // Nothing more to do.
        }
        if (j > 0)
            ret += str[i..i+j-1];
	DEBUG("ret = <" + ret + ">")
        i += j;

        chr = str[i..i];
        if (i+1 == slen || str[i+1..i+1] == chr)
        {
             ret += chr;
             i ++;
        }
        else 
        {
            for_obj = (chr == "$") ? subj : obj;
            for (j=1; i+j<slen && is_char(str[i+j]); j++)
                /* Do nothing. */;

            if (j == 1) 			       // Next is *not* a char.
            {
                if (str[i+1] == '{')                   // Next is {, i.e. ${text}
                {
                    j = member_array("}", buf[i+1..slen]);
                    if (j == -1) 
                    {
                        ret += chr; i++; continue; 
                    }
		    
                    k = member_array(";", buf[i+1..i+1+j]);

		    // if (subj->query_name()=="Rogon")
		    //     subj->catch_msg(str[i+1..-1]+"\n"+i+","+j+","+k+"\n");
		    
                    if (k == -1)                        // No ; found.
                        ret += V_FOR(for_obj, 
				     replace_specs(str[i+2..i+j], subj, obj));
                    else 
                        ret += V_FOR2(for_obj, 
				      replace_specs(str[i+2..i+k], subj, obj), 
				      replace_specs(str[i+k+2..i+j], subj, obj));
                    i += j+2;
                    continue;
                }
		ret += chr; i++; continue; 
            }
	    else if (j == 2) 		                // $N etc.
            {
                if (i+3 < slen && str[i+2]=='\'' && str[i+3] == 's') // 's
                    if (str[i+1] == 'n')
                    {
                        ret += VPOSS(for_obj);
                        i += 4;
                        continue;
                    }
                    else if (str[i+1] == 'N')
                    {
                        ret += VCPOSS(for_obj);
                        i += 4;
                        continue;
                    }
                  
                switch (str[i+1])  // Checking $N, #p etc. syntax.
                {
                    case 'N' : ret += VCTNAME(for_obj); break;
                    case 'n' : ret += VTNAME(for_obj); break;
                    case 'S' : ret += VCHE_SHE(for_obj); break;
                    case 's' : ret += VHE_SHE(for_obj); break;
                    case 'O' : ret += VCHIM_HER(for_obj); break;
                    case 'o' : ret += VHIM_HER(for_obj); break;
                    case 'P' : ret += VCHIS_HER(for_obj); break;
                    case 'p' : ret += VHIS_HER(for_obj); break;
                    case 'r' : ret += VSELF(for_obj); break;
                    default:   ret += str[i..i+1]; 
                }
                i += 2;
            }
            else
            {
                switch (str[i+1..i+j-1])
		{
		case "Name":
                case "You":     ret += VCTNAME(for_obj); break;
		case "name":
                case "you":     ret += VTNAME(for_obj); break;
                case "Names":   ret += VCPOSS(for_obj); break;
                case "names":   ret += VPOSS(for_obj); break;
                case "_You":
		case "He":      ret += VCHE_SHE(for_obj); break;
                case "_you":
		case "he":      ret += VHE_SHE(for_obj); break;
		case "Him":     ret += VCHIM_HER(for_obj); break;
		case "him":     ret += VHIM_HER(for_obj); break;
                case "Your":    
		case "His":     ret += VCHIS_HER(for_obj); break;
                case "your":
                case "his":     ret += VHIS_HER(for_obj); break;
                case "yourself":
		case "himself": ret += VSELF(for_obj); break;
                case "race":    ret += for_obj->query_race_name(); break;
                case "nonmet":  
		case "nonmetname":
                                ret += for_obj->query_nonmet_name(); break;
		case "verb":    ret += VVERB(query_verb(), for_obj);
		default:        ret += VVERB(str[i+1..i+j-1], for_obj);
		}
                i += j;
            }           
        }
    } // End endless loop.
}                

string
tellem_format(string str, object subj, object obj)
{
    LIB_FILE->teleledningsanka();
    str = replace_specs(str, subj, obj);
    str = replace_braces(str, subj, obj);

    if (find_player("rogon")) {
	FIXEUID;
	log_file("TELLEM", str + "\n", 1000);
    } 
    return str;
}

/*
 * Function name:   TellRoom
 * Arguments:	    object subj     - The subject.
 *		    object obj	    - The object.
 *		    string format   - The tellem format string.
 * Description:     Produces a text to all in a room.
 */
void
TellRoom(object subj, object obj, string format)
{
    tell_room(ENV(subj), tellem_format(format, subj, obj));
}


/*
 * Function name:   Tell
 * Arguments:	    object subj     - The subject.
 *		    object obj	    - The object.
 *		    string format   - The tellem format string.
 * Description:     Produces a text to all in a room, where only
 *		    those seeing fights also seeing both the
 *		    subject and the object (if it is a living)
 *		    get any text.
 */
void
Tell(object subj, object obj, string format)
{
    object *to_tell = INV(ENV(subj));
    to_tell -= ({ subj });
    to_tell -= ({ obj });
    to_tell = ({ subj, obj }) + filter(to_tell, &->query_option(OPT_BLOOD));
    
    to_tell->catch_msg(tellem_format(format, subj, obj));
}

varargs void
Write(mixed arg1, mixed arg2 = TP)
{
    object tp;
    string str;

    if(stringp(arg1))
	str = arg1;
    if(objectp(arg1))
	tp = arg1;
    if(stringp(arg2))
	str = arg2;
    tp->catch_msg(tellem_format(str, tp, 0));
}

/*
 * Function name:   tellem
 * Arguments:	    object a	 - The attacker (subject)
 *		    object v	 - The victim	(object)
 *		    string str	 - The tellem format string.
 *		    int tell_all - Tell all, or just those seeing fights?
 * Description:     Uses the tellem format for use when one object (attacker)
 *		    does something with another object (victim).
 * Examples:
 *  tellem(find_player("rogon"), find_player("casanova"),
 *	"(You) hew[s] (his) head off with a mighty swing!\n" +
 *	"{"+
 *	   "(His) head rolls at the floor as [his] blood gushes and covers\n"+
 *	   "the earth in front of (you).\n" +
 *	";"+
 *	   "You die in a terrible scene of blood as your head is decapitated!\n"+
 *	";*}", 1);
 *
 * Rogon will get:
 *     You hew Casanova's head off with a mighty swing!
 *     Casanova's head rolls at the floor as his blood gushes and covers
 *     the earth in front of you.
 * Casanova will get:
 *     Rogon hews your head off with a mighty swing!
 *     You die in a terrible scene of blood as your head is decapitated!
 * Other will get:
 *     The white-bearded dwarf wizard hews Casanova's head off with a mighty swing!
 *     Casanova's head rolls at the floor as his blood gushes and covers
 *     the earth in front of the white-bearded dwarf wizard.
 * (Assuming that they have met Casanova, but not Rogon, and that
 *  Casanova and Rogon have met.)
 */

/*
 * Function name:   tellem
 * Arguments:	    subjective	(object)
 *			The object which is the subject of the action.
 *		    objective	(object)
 *			The object which is the object of the action.
 *		    text	(string)
 *			The special tellem format.
 *		    tell_all	(int)
 *			0 [default] : Tell only those who see fights.
 *			1	    : Tell all in this room.
 * Description:
 *	This routine is special, since it includes outputing of text
 *	to involved parties in one special tellem format. This format
 *	is specified below.
 */
varargs void
tellem( object subj, object obj, string text, int tell_all = 0)
{
    if (tell_all)
	TellRoom(subj, obj, text);
    else 
	Tell(subj, obj, text);
}

varargs void
tellbb(string str, object target, object tp = TP)
{
    object *who = FILTER_LIVE(INV(ENV(tp))) - ({ tp }) - ({ target });
    who = FILTER_CAN_SEE(who, tp);
    who->catch_msg(tellem_format(str, tp, target));
}

varargs void
tellme(string str, object target = 0, object tp = TP)
{
    tp->catch_msg(tellem_format(str, tp, target));
}

/*
 * Function name:   action
 * Arguments:	    string form     - Tellem-style format of an action.
 *		    object to_whom  - Who's the reciever of the action.
 *				      Optional.
 * Description:     Describes an action taking place in a room. Assumes
 *		    that the action can be watched even if you can't see
 *		    the person in the room.
 */
varargs void
action(string form, object to_whom = 0)
{
    tell_room(ETP, tellem_format(form, TP, to_whom));
}

/*
 * Function name:   silent_action
 * Arguments:	    string form     - Tellem-style format of an action.
 *		    object to_whom  - Optional direct object of the action.
 * Description:     Describes a silent action taking place in this_player's
 *		    room.
 */
varargs void
silent_action(string form, object to_who = 0)
{
    object *can_see = FILTER_CAN_SEE(INV(ETP), TP) + ({ TP });

    can_see->catch_msg(tellem_format(form, TP, to_who));
}

/*
 * Function name:   produce_message
 * Arguments:	    object attacker - The attacker.
 *		    object enemy    - The enemy.
 *		    int phurt	    - How hurt.
 *		    string *desc    - Description array (See below.)
 *	      [Opt] mapping extra   - Extra replacing.
 * Description:
 *	Example of how to produce combat messages nicely and easily.
 *	The desc array consists of an array where
 *
 *	    desc[0]	: What message to produce when completely missing.
 *	    desc[1]	: What message to produce when almost hitting.
 *	    desc[2..]	: Messages of increasing severity.
 *
 *	All messages are in the tellem format defined above. $ is the attacker,
 *	# the victim. The extra array can be used for extra replacing.
 */
varargs void
produce_message(object attacker, object enemy, int phurt, string *desc,
		mapping extra = ([]))
{
    int size;
    int no;
    string mess;

    switch(phurt)
    {
	case -1: no = 0; break;
	case  0: no = 1; break;
	default: size = sizeof(desc) - 2;
		 no = ftoi(pow(itof(phurt-1)/100.0, 0.4) * itof(size));
		 if (no >= size) no = size - 1;
		 no += 2;
    }
    mess = desc[no];
    tellem(attacker, enemy, smart_replace(mess, extra) + "\n");
}
