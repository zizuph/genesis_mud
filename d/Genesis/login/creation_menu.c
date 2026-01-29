/*
 * creation_menu.c
 *
 * Module allowing players to select their features.
 */

#include <login.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/race/racial_abilities.h"

#define MAX_PHASES 6
#define PHASE_DESCS ({ "Body", "Race", "Racial Abilities", \
   "Gender", "Adjective 1", "Adjective 2", \
   "Order", "Height", "Weight", "Confirm" })

#define RACIAL_PHASE_DESCS ({ "Body", "Racial Abilities", "Confirm" })

#define DEATH_CHOICES ({ "Continue with same character", \
   "Change race or gender", "Change description only" })
#define CONFIRM_CHOICES ({ "Confirm" })
#define GENDER_CHOICES ({ "male", "female" })
#define GENERAL_CATEGORY ("general")
#define NEW_ATTRIBUTES_CHOICES ({ "Pick new attributes" })
#define MAIN_PHASE (phase / 10)
#define SUB_PHASE  (phase % 10)

#define PHASE_DEATH          0
#define PHASE_DEATH_CONFIRM  1
#define PHASE_RACE          10
#define PHASE_RACIAL        20
#define PHASE_GENDER        30
#define PHASE_CATEGORY1     40
#define PHASE_ATTRIBUTE1    41
#define PHASE_CATEGORY2     50
#define PHASE_ATTRIBUTE2    51
#define PHASE_ATTRIB_ORDER  60
#define PHASE_HEIGHT        70
#define PHASE_WIDTH         80
#define PHASE_ALL_CONFIRM   90
#define PHASE_RACIAL_ONLY   15
#define PHASE_RACIAL_ONLY_CONFIRM 25
#define PHASES ({ PHASE_DEATH, PHASE_DEATH_CONFIRM, PHASE_RACE, PHASE_RACIAL, \
    PHASE_GENDER, PHASE_CATEGORY1, PHASE_ATTRIBUTE1, \
    PHASE_CATEGORY2, PHASE_ATTRIBUTE2, PHASE_ATTRIB_ORDER, PHASE_HEIGHT, \
    PHASE_WIDTH, PHASE_ALL_CONFIRM })

#define ATTRIBUTE_DIR ("/d/Genesis/login/attributes/")
#define HINTS_DIR     ("/d/Genesis/login/help/")
#define HINT_FILENAME(phase) (HINTS_DIR + "hint_phase_" + (phase) + ".txt")
#define RACIAL_HINT_FILENAME(name)  (HINTS_DIR + "hint_ability_" + (implode(explode(name, " "), "_")) + ".txt")
#define DOC_LOGIN_RACES ("/d/Genesis/doc/login/RACES")

#define RACIAL_ONLY_PHASES ({ PHASE_RACIAL_ONLY, PHASE_RACIAL_ONLY_CONFIRM })

/* Global variables. */
/* Phase is a 2 digit number. The tens are the main phase, the second digit
 * is the sub phase (if any), or 0 */
int phase;

int * available_phases;
string * phase_descs;
string menu_title;
string bad_command_message;

int gender;
string category1, category2;
string attribute1, attribute2;
string racial_ability1, racial_ability2;
int height;
int width;
string race;
string *choices;
function restart_function;

/* Prototypes */
void ask_question(int full);
void finish_body();
void finish_racial();
void start();
void start_racial();

void
create()
{
    setuid();
    seteuid(getuid());
}

void
previous_phase()
{
    int index = member_array(phase, available_phases);

    index = ((index > 0) ? --index : 0);
    phase = available_phases[index];
}

void
next_phase()
{
    int index = member_array(phase, available_phases);

    index = ((index < (sizeof(available_phases) - 1)) ? ++index : 0);
    phase = available_phases[index];
}

public void linkdeath_hook(object player, int linkdeath)
{
    if (!linkdeath)
    {
        restart_function();
    }
}


void
process_answer(string str)
{
    int answer = atoi(str);
    string tmp;

    if (IN_ARRAY(str, ({ "q", "quit", "s", "stop", "cancel" }) ))
    {
	    if (member_array(phase, RACIAL_ONLY_PHASES) == -1)
        {
            this_player()->quit();
        }
	    destruct();
	    return;
    }
    if (IN_ARRAY(str, ({ "?", "h", "help" }) ))
    {
	if (phase == PHASE_RACE)
	{
	    cat(DOC_LOGIN_RACES);
	}
        ask_question(0);
        return;
    }
    
    if (!strlen(str))
    {
        bad_command_message = ("The answer \"" + str + "\" was not recognised.\n");
        ask_question(0);
        return;
    }    

    /* Player wants to go back. */
    str = lower_case(str);
    if ((str == "0") || (str == "back"))
    {
        /* Allow the player to go back, or ask again. */
        if ((phase != PHASE_DEATH) && (phase != PHASE_RACE))
        {
            previous_phase();
            ask_question(1);
            return;
        }
        else
        {
            bad_command_message = ("You cannot go back at this phase.\n");
            ask_question(0);
            return;
        }    
    }
    
    if (phase == PHASE_RACIAL || phase == PHASE_RACIAL_ONLY)
    {
        int answer1, answer2;
        string text1, text2;
        if (parse_command(str, ({}), "%d [and] %d", answer1, answer2))
        {
            text1 = "" + answer1;
            text2 = "" + answer2;
            answer1--;
            answer2--;
        }
        else if (parse_command(str, ({}), "%s 'and' %s", text1, text2))
        {
            answer1 = member_array(text1, choices);
            answer2 = member_array(text2, choices);
        }
        else
        {
            bad_command_message = ("You must pick two options.\n");
            ask_question(0);
            return;
        }
        if (answer1 < 0 || answer1 >= sizeof(choices))
        {
            bad_command_message = ("The answer \"" + text1 + "\" was not recognised.\n");
            ask_question(0);
            return;
        }
        if (answer2 < 0 || answer2 >= sizeof(choices))
        {
            bad_command_message = ("The answer \"" + text2 + "\" was not recognised.\n");
            ask_question(0);
            return;
        }
        if (answer1 == answer2)
        {
            bad_command_message = ("You cannot pick " + choices[answer1] + " twice.\n");
            ask_question(0);
            return;
        }
        racial_ability1 = choices[answer1];
        racial_ability2 = choices[answer2];
        write("You have chosen " + racial_ability1 + " and " + racial_ability2 +
            " as your two choices.\n");
        next_phase();
        ask_question(1);
        return;

    }
    
    /* Numerical answer that is not correct. */
    if ((answer < 0) || (answer > sizeof(choices)))
    {
        bad_command_message = ("The answer \"" + str + "\" was not recognised.\n");
        ask_question(0);
        return;
    }

    /* Convert numerical answer to string answer and vice versa. */
    if (answer > 0)
    {
        answer--;
        str = choices[answer];
    }
    else
    {
        answer = member_array(str, choices);
    }
    /* Invalid choice. */
    if (answer == -1)
    {
        bad_command_message = ("The answer \"" + str + "\" was not recognised.\n");
        ask_question(0);
        return;
    }

    switch(phase)
    {
    case PHASE_DEATH:
        break;
    case PHASE_DEATH_CONFIRM:
        /* Confirmation only. No action necessary. */
        break;
    case PHASE_RACE:
        /* Race choice is the same as the answer. */
        race = RACES[answer];
        write("You have selected to be: " + LANG_ADDART(race) + "\n");
        break;
    case PHASE_GENDER:
        /* Gender choice is the same as the answer. */
        gender = answer;
        write("You have selected to be: " + LANG_ADDART(GENDER_CHOICES[gender]) + " " + race + "\n");
        break;
    case PHASE_CATEGORY1:
        /* Category 1 choice is the same as the answer. */
        category1 = choices[answer];
        break;
    case PHASE_ATTRIBUTE1:
        /* Attribute 1 choice is the same as the answer. */
        attribute1 = choices[answer];
        write("You have selected to be: " + LANG_ADDART(attribute1) + " ... " + GENDER_CHOICES[gender] + " " + race + "\n");
        break;
    case PHASE_CATEGORY2:
        /* Category 2 choice is the same as the answer. */
        category2 = choices[answer];
        break;
    case PHASE_ATTRIBUTE2:
        /* Attribute 2 choice is the same as the answer. */
        attribute2 = choices[answer];
        write("You have selected to be: " + LANG_ADDART(attribute1) + " " + attribute2 + " " + GENDER_CHOICES[gender] + " " + race + "\n");
        break;
    case PHASE_ATTRIB_ORDER:
        /* Player wishes to swap attributes. */
        if (answer == 1)
        {
            tmp = attribute1;
            attribute1 = attribute2;
            attribute2 = tmp;
            tmp = category1;
            category1 = category2;
            category2 = tmp;
        }
        /* New adjectives. */
        if (answer == 2)
        {
            phase = PHASE_CATEGORY1;
            ask_question(1);
            return;
        }
        write("You have selected to be: " + LANG_ADDART(attribute1) + " " + attribute2 + " " + GENDER_CHOICES[gender] + " " + race + "\n");
        break;
    case PHASE_HEIGHT:
        /* Height choice is the same as the answer. */
        height = answer;
        write("You have selected to be: " + HEIGHTDESC[height] + " for " + LANG_ADDART(GENDER_CHOICES[gender]) + " " + race + "\n");
        break;
    case PHASE_WIDTH:
        /* Width choice is the same as the answer. */
        width = answer;
        write("You have selected to be: " + HEIGHTDESC[height] + " and " + WIDTHDESC[width] + " for " + LANG_ADDART(GENDER_CHOICES[gender]) + " " + race + "\n");
        break;
    case PHASE_ALL_CONFIRM:
        /* Confirmation only. No action necessary. */
        write("All done.\n");
        finish_body();
        return;
        /* Follow up code after confirmation to go here.*/
        break;
    case PHASE_RACIAL_ONLY_CONFIRM:
        /* Confirmation only. No action necessary. */
        write("All done.\n");
        finish_racial();
        return;
        /* Follow up code after confirmation to go here.*/
        break;
    default:
    }

    next_phase();
    ask_question(1);
}

string get_hint_text(int phase)
{
    if (phase == PHASE_RACIAL || phase == PHASE_RACIAL_ONLY)
    {
        string hints = "";
        foreach (string choice : choices)
        {
            string filename = RACIAL_HINT_FILENAME(choice);
            hints += implode(explode(read_file(filename), "\n")[0..1], "\n");
            hints += "\n\n";
        }
        return hints;
    }
    return read_file(HINT_FILENAME(phase));
}

/*
 * Function name: read_hint
 * Description  : 
 * Arguments    : int line_left - the amount of space left on the line. This
 *                   is used in case a single line of text is appended to the
 *                   right of a selection of choices.
 * Returns      : 
 */
string *
read_hint(int line_left)
{
    int index;
    int size;
    string *lines;

    lines = explode(get_hint_text(phase), "\n");
    size = sizeof(lines) - 1;
    /* If the lines end with a \ then concatenate the text. */
    while(--size >= 0)
    {
        if (lines[size][-1..] == "\\")
        {
            lines[size] = lines[size][..-2] + lines[size + 1];
            lines = exclude_array(lines, size+1, size+1);
        }
    }
    /* If there are multiple lines, it's meant to be split. */
    if (sizeof(lines) > 1)
    {
        return lines;
    }
    /* Concatenate the string into a single line, then break it into smaller
     * bits to fit the line length and return it in an array. */
    return explode(HANGING_INDENT(implode(lines, ""), 1, line_left), "\n");
}

string *
pad_choices(string *padded)
{
    int index;
    int size = sizeof(padded);
    int choice_length = applyv(max, map(padded, strlen)); 

    /* Align all to the longest choice. */
    padded = map(padded, &sprintf("] %-*s", choice_length, ));
    /* Add the index numbering. */
    for (index = 0; index < size; index++)
    {
        padded[index] = " [" + (index + 1) + padded[index];
    }
    /* This line will make sure that the indices 1..9 get an extra space. */
    padded = map(padded[..8], &operator(+)(" ", )) + padded[9..];
    if (phase == PHASE_RACIAL || phase == PHASE_RACIAL_ONLY)
    {
        string * new_padded = ({});
        string empty = sprintf("%*s", choice_length + 6, "");
        for (index = 0; index < size; index++)
        {
            new_padded += ({ upper_case(padded[index]), empty, empty });
        }
        padded = new_padded;   
    }
    /* Add a question mark for help. */
    if (phase == PHASE_RACE)
    {
        padded += ({ sprintf("  [?] %-*s", choice_length, "help") });
    }
    /* No 'back' button for death and race selection. */
    if ((phase != PHASE_DEATH) && (phase != PHASE_RACE) && (phase != PHASE_RACIAL_ONLY))
    {
        padded += ({ sprintf("  [0] %-*s", choice_length, "back") });
    }
    if ((phase == PHASE_RACIAL_ONLY))
    {
        padded += ({ sprintf("  [q] %-*s", choice_length, "cancel") });
    }
    return padded;
}

void
ask_question(int full)
{
    int index;
    int size;
    string *padded;
    int choice_length, line_left;
    string *lines;

    switch(phase)
    {
    case PHASE_DEATH:
        choices = DEATH_CHOICES;
        break;
    case PHASE_DEATH_CONFIRM:
        choices = CONFIRM_CHOICES;
        break;
    case PHASE_RACE:
        choices = RACES;
        break;
    case PHASE_RACIAL:
    case PHASE_RACIAL_ONLY:
        choices = ({});
        foreach (int ability : RACE_TO_ABILITIES[race])
        {
            choices += ({ ABILITIES_TO_NAME[ability] });
        }
        break;
    case PHASE_GENDER:
        choices = GENDER_CHOICES;
        break;
    case PHASE_CATEGORY1:
        choices = get_dir(ATTRIBUTE_DIR + "*") - ({ ".", ".." });
        break;
    case PHASE_ATTRIBUTE1:
        choices = explode(read_file(ATTRIBUTE_DIR + category1), "\n");
        break;
    case PHASE_CATEGORY2:
        choices = get_dir(ATTRIBUTE_DIR + "*") - ({ ".", ".." });
        if (category1 != GENERAL_CATEGORY)
        {
            choices -= ({ category1 });
        }
        break;
    case PHASE_ATTRIBUTE2:
        choices = explode(read_file(ATTRIBUTE_DIR + category2), "\n");
        choices -= ({ attribute1 });
        break;
    case PHASE_ATTRIB_ORDER:
        choices = ({ attribute1 + " " + attribute2 + " " + GENDER_CHOICES[gender] + " " + race });
        choices += ({ attribute2 + " " + attribute1 + " " + GENDER_CHOICES[gender] + " " + race });
        choices += NEW_ATTRIBUTES_CHOICES;
        break;
    case PHASE_HEIGHT:
        choices = HEIGHTDESC;
        break;
    case PHASE_WIDTH:
        choices = WIDTHDESC;
        break;
    case PHASE_ALL_CONFIRM:
    case PHASE_RACIAL_ONLY_CONFIRM:
        choices = CONFIRM_CHOICES;
        break;
    default:
        choices = ({ "Phase error: " + phase });
    }

    padded = pad_choices(choices);
    size = sizeof(padded);
    /* Make into an even number if two columns are needed. */
    if ((sizeof(choices) > 10) && (size % 2 == 1))
    {
        padded += ({ "" });
        size++;
    }

    if (full)
    {
        write(menu_title + " -= Phase " + MAIN_PHASE + ": " + phase_descs[MAIN_PHASE] + " Selection =-\n");
    }
    write("\n");
    if (phase == PHASE_ALL_CONFIRM)
    {
        write("You have selected to be " + LANG_ADDART(attribute1) + " " + attribute2 + " " + GENDER_CHOICES[gender] + " " + race + ".\n");
        write("You have also selected to be " + HEIGHTDESC[height] + " and " + WIDTHDESC[width] + " for " + LANG_ADDART(GENDER_CHOICES[gender]) + " " + race + ".\n");
    }
    if (phase == PHASE_ALL_CONFIRM || phase == PHASE_RACIAL_ONLY_CONFIRM)
    {
        write("You have chosen " + racial_ability1 + " and " + racial_ability2 + " as your racial abilities.\n\n");
    }

    /* If we have more than 10 choices, we go to two columns. */
    if (sizeof(choices) > 10)
    {
        size /= 2;
        for (index = 0; index < size; index++)
        {
            padded[index] += " " + padded[index + size];
        }
        padded = padded[..(size-1)];
    }
    /* Get the hint text. */
    line_left = 77 - strlen(padded[0]);
    lines = read_hint(line_left);

    /* If we have more choices than help, pad the help. */
    if (size > sizeof(lines))
    {
        for (index = sizeof(lines); index < size; index++)
        {
            lines += ({ "" });
        }
    }
    /* If we have fewer choices than help, pad the choices. */
    if (size < sizeof(lines))
    {
        string pad = "";
        for (int i = 0; i < strlen(padded[0]); i++)
        {
            pad += " ";
        }
        for (index = size; index < sizeof(lines); index++)
        {
            padded += ({ pad });
        }
        size = sizeof(lines);
    }
    
    int pad_len = strlen(padded[0]);
    /* Print choices and hints. */
    for (index = 0; index < size; index++)
    {
        write(padded[index] + "  " + lines[index] + "\n");
    }
    write("\n");
    if (strlen(bad_command_message))
    {
        write(bad_command_message);
        bad_command_message = "";
    }
    if (phase == PHASE_RACIAL || phase == PHASE_RACIAL_ONLY)
    {
       write("Enter your two choices (e.g. \"1 and 2\"): ");
    }
    else
    {
       write("Enter your choice: ");
    }
    input_to(process_answer);
}

void
start()
{
    available_phases = PHASES;
    phase = PHASE_RACE;
    phase_descs = PHASE_DESCS;
    menu_title = "Character Creation";
    restart_function = &start();
    ask_question(1);
}

void
start_racial()
{
    available_phases = RACIAL_ONLY_PHASES;
    phase = PHASE_RACIAL_ONLY;
    phase_descs = RACIAL_PHASE_DESCS;
    race = this_player()->query_race();
    menu_title = "Racial Abilities";
    restart_function = &start_racial();
    ask_question(1);
}

void set_racial_ability_skills()
{
    int racial_skill = 0;
    foreach (int id, string name : ABILITIES_TO_NAME)
    {
        if (name == racial_ability1 || name == racial_ability2)
        {
            racial_skill |= id;
        }
    }
    this_player()->set_skill(RACIAL_ABILITY_SKILL, racial_skill);
    this_player()->configure_racial_bonuses();
}

void finish_racial()
{
    set_racial_ability_skills();
    destruct();
}


/*
 * Setup the new body according to the previous choices.
 *
 * Then clear GP_BODY and send him on his way.
 */
void
finish_body()
{
    mixed race_attr = RACEATTR[race];
    
    this_player()->set_race_name(race);
    this_player()->set_gender(gender);
    
    this_player()->remove_adj(this_player()->query_adj(-1));
    this_player()->set_adj(({ attribute1, attribute2 }));

    height = (race_attr[0] * SPREAD_PROC[height]) / 100 -
        random(race_attr[0] / 20);
    this_player()->add_prop(CONT_I_HEIGHT, height);
    
    width = (race_attr[5] * this_player()->query_prop(CONT_I_HEIGHT) *
        (width + 7) / 10);
    width = width - random(width * race_attr[5] / 8000);
    this_player()->add_prop(CONT_I_WEIGHT, width);
    this_player()->add_prop(CONT_I_VOLUME, width);
    
    set_racial_ability_skills();

    /*
     * If the player has GP_TUTORIAL set it's a new player
     * New players needs stats etc.
     */
    if (this_player()->query_ghost() & GP_TUTORIAL)
    {
        int il;

        for (il == SS_STR; il < SS_NO_EXP_STATS; il++)
	{
            this_player()->set_base_stat(il, RACESTAT[race][il]);
	}
        
        this_player()->set_learn_pref(0);
        this_player()->stats_to_acc_exp();

        this_player()->set_hp(this_player()->query_max_hp());
        this_player()->set_mana(this_player()->query_max_mana());
        this_player()->set_fatigue(this_player()->query_max_fatigue());
    }
    
    /* We're finished here, on to the next step if one is needed. */
    this_player()->set_ghost(this_player()->query_ghost() & ~GP_BODY & ~GP_NOSKILL_LOSS);
    this_player()->ghost_ready();
    destruct();
}
