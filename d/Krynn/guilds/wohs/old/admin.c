/*
 * This is the new master of the Wizards of High Sorcery
 *
 * Conclave; Three members; One head; One from each Order
 * Apprentice; Reds; Whites; Blacks
 * Levels of Apprentice < needs mentors. 
 */

#include "guild.h"

#define M_LEVEL     0  /* I The last level we saw this member at */
#define M_COLOR     1  /* S The color of the robe, or Apprentice */
#define M_SPELLS    2  /* S Bitlist of the spells of the member */
#define M_STUDENTS  3  /* AS Students of this member */
#define M_MENTOR    4  /* S The mentor */
#define M_XP        5  /* I The spell experience  */
#define M_DATA      6  /* M Mapping containing any data */
#define M_SIZE      7

#define R_TIME      0  /* I When the member was declared renegade */
#define R_REASON    1  /* S Why? */
#define R_BANE      2  /* S Who? */
#define R_SIZE      3  

string conclave_head;
string *conclave_members;
mapping members;
mapping renegades;
mixed *spells;


int add_student(string mentor, string student);
int remove_student(string mentor, string student);
int remove_conclave_member(string who);


void
create()
{
    setuid();
    seteuid(getuid());
    
    conclave_members = ({ });
    members = ([ ]);
    renegades = ([ ]);

    restore_object(LOG + "admin");
}

void
save()
{
    save_object(LOG + "admin");
}

void
remove_object()
{
    save();
}

int
add_student(string mentor, string student)
{
    /* Can't have both students and a mentor */
    if (!members[mentor] ||
        members[mentor][M_MENTOR])
        return 0;
    
    /* If the student has a mentor, get rid of him */
    if (members[student][M_MENTOR])
        remove_student(members[student][M_MENTOR], student);
    
    members[student][M_MENTOR] = mentor;
    if (!pointerp(members[mentor][M_STUDENTS]))
        members[mentor][M_STUDENTS] = ({ });

    members[mentor][M_STUDENTS] += ({ student });

    return 1;
}

int
remove_student(string mentor, string student)
{
    if (members[mentor])
    {
        if (!pointerp(members[mentor][M_STUDENTS]))
            members[mentor][M_STUDENTS] = ({ });
        members[mentor][M_STUDENTS] -= ({ student });
    }

    if (members[student])
    {
        members[student][M_MENTOR] = 0;
    }
    
    return 1;
}

varargs int
add_member(mixed who, mixed mentor)
{
    if (objectp(who))
        who = who->query_real_name();

    if (objectp(mentor))
        mentor = mentor->query_real_name();

    if (!who || members[who])
        return 0;
    
    members[who] = allocate(M_SIZE);
    members[who][M_SPELLS] = "";
    members[who][M_LEVEL] = 0;
    members[who][M_COLOR] = INITIATE;
    members[who][M_STUDENTS] = ({ });
    
    if (mentor)
        add_student(mentor, who);
    
    return 1;
}

public int
remove_member(mixed who)
{
     if (objectp(who))
         who = who->query_real_name();
     
     if (!members[who])
         return 0;

     if (member_array(who, conclave_members) >= 0)
     {
         conclave_members -= ({ who });
         if (conclave_head == who)
             conclave_head = 0;
     }

     if (members[who][M_MENTOR])
         remove_student(members[who][M_MENTOR], who);

     if (sizeof(members[who][M_STUDENTS]))
     {
         map(members[who][M_STUDENTS], &remove_student(who, ));
     }

     if (renegades[who])
         renegades = m_delete(renegades, who);
     
     members = m_delete(members, who);
     return 1;
}

public int
query_member(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    return !!members[who];
}

/*
 * Function Name: change_order
 * Description  : Moves someone from one guild order to another.
 *
 */
public int
change_order(mixed who, string order)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    if (members[who][M_COLOR] == order)
        return 0;

    /* Before we change the order we need to clear conclave status */
    remove_conclave_member(who);

    members[who][M_COLOR] = order;
}

/*
 * Function Name: add_renegade
 * Description  : Mark someone as a renegade.
 *                Renegades are still ordinary mages, their ties to the
 *                tower are cut though.
 * Arguments    : mixed - who
 *                mixed - actor
 * Returns      : true on success
 */
public int
add_renegade(mixed who, mixed actor, string reason)
{
     if (objectp(who))
        who = who->query_real_name();
     
     if (objectp(actor))
         actor = actor->query_real_name();
     
     if (!actor || !who || !members[who] || renegades[who])
         return 0;
     
     /* Only full mages can be renegades */
     if (members[who][M_COLOR] == INITIATE)
         return 0;
     
     renegades[who] = ({ time(), reason, actor });
     
     /* Renegade and conclave member is no good */
     remove_conclave_member(who);
     
     return 1;
}


public int
query_renegade(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
      
    return !members[who] || !renegades[who];
}

varargs string *
query_members(string color)
{
    mapping tmap;
    if (color)
    {
        /* Hail to the mother of all filters */
        tmap = filter(members, &operator(==)(color) @ 
            &operator([])(, M_COLOR));
        return m_indexes(tmap) - m_indexes(renegades);
    }
    
    return m_indexes(members) - m_indexes(renegades);
}

public varargs string *
query_renegades(string color)
{
    mapping tmap;
    if (color)
    {
        /* Hail to the mother of all filters */
        tmap = filter(members, &operator(==)(color) @ 
            &operator([])(, M_COLOR));
        return m_indexes(tmap) & m_indexes(renegades);
    }
    
    return m_indexes(members) & m_indexes(renegades);
}

/*
 * Function name: query_conclave_head
 * Description:   Return the name of the Head of the Order.
 *                If no argument is given you will get the head of
 *                the council.
 * Arguments:     order - The order asked for.
 * Returns:       A name or False.
 */  
varargs string
query_conclave_head(string order)
{
    int size;
    
    if (!order)
        return conclave_head;
    
    size = sizeof(conclave_members);
    
    while (size--)
    {
        if (members[conclave_members[size]][M_COLOR] == order)
            return conclave_members[size];
    }

    return 0;
}

int
set_conclave_head(string who)
{
    if (member_array(who, conclave_members) < 0)
        return 0;
    
    conclave_head = who;
    return 1;
}

int
add_conclave_member(string who)
{
    if (!members[who])
        return 0;

    /* This is auto, there has to be one */
    if (!conclave_head)
        conclave_head = who;
    
    conclave_members += ({ who });
    return 1;
}

int
remove_conclave_member(string who)
{
    if (member_array(who, conclave_members) < 0)
    {
        return 0;
    }

    if (conclave_head == who)
        conclave_head = 0;

    conclave_members -= ({ who });
    return 1;
}

string *
query_conclave_members()
{
    return conclave_members || ({ });
}

int
query_conclave_member(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    return (member_array(who, conclave_members) >= 0);
}


string
query_member_type(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return "";

    return members[who][M_COLOR];
}

/* 
 * WoHS Level stuff
 * This is really uncertain ...
 */
int
query_member_level(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    return members[who][M_LEVEL];    
}

/*
 * Called from shadow at logout etc
 */
int
update_member_level(object who)
{
    string name;
    
    name = who->query_real_name();
    
    if (!members[name])
        return 0;
    
    members[name][M_LEVEL] = who->query_wohs_level();
    members[name][M_XP] = who->query_wohs_xp();
}
    
/*
 * General Data Saving Routines
 */

/*
 * Function Name: query_data
 * Description  : Returns the data saved under the players "index" key.
 *                This can be any kind of variable.
 * Arguments    : mixed - the player
 *               string - the data index
 */
public mixed
query_data(mixed who, string index)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    if (!members[who][M_DATA])
        return 0;
    
    return members[who][M_DATA][index];
}

/*
 * Function Name: set_data
 * Description  : Saves a variable using the index name.
 *                This should be used to save any "non important" data
 *                which is player specific. Such as teleport destinations
 *                and things like that.
 * Arguments    : mixed - the player
 *               string - the data index
 *                mixed - the data to save.
 */
public void
set_data(mixed who, string index, mixed data)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return;
    
    if (!mappingp(members[who][M_DATA]))
        members[who][M_DATA] = ([ ]);
    
    members[who][M_DATA][index] = data;
}

/*
 * Spell Bits
 * 
 * These control the spell availability of a mage.
 */
public int
query_spell(mixed who, int spell)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    return efun::test_bit(members[who][M_SPELLS], spell);
}

public void
set_spell(mixed who, int spell)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    members[who][M_SPELLS] = efun::set_bit(members[who][M_SPELLS], spell);
}

public void
clear_spell(mixed who, int spell)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;
    
    members[who][M_SPELLS] = efun::clear_bit(members[who][M_SPELLS], spell);
}

/*
 * Some General wiz Info stuff.
 */
static string
order_info(string order)
{
    string ret;
    string *names;
    int i, k;

    ret = "The Master of the " + order + " is: " + 
        (query_conclave_head(order) ? capitalize(query_conclave_head(order)) :
            "None");
    ret += "\n";
    
    names = sort_array(query_members(order));

    i = -1;
    k = sizeof(names);
    while (++i < k)
    {
        ret += sprintf("%11s - Mentor: %-11s Students: %s\n", 
            capitalize(names[i]),
            (members[names[i]][M_MENTOR] ? 
                capitalize(members[names[i]][M_MENTOR]) : "None"),
            (sizeof(members[names[i]][M_STUDENTS]) ? 
                implode(map(members[names[i]][M_STUDENTS], capitalize), ", ") :
                "None"));
    }
    
    ret += "\n";

    return ret;
}

/* TODO */
string
stat_object()
{
    string *tmp;
    string ret;
    int index, size;

    ret = "WoHS Admin Info\n";
    
    if (stringp(conclave_head))
    {
        ret += "The Head of the Conclave is: " + capitalize(conclave_head)
            + "\n";
    }
    
    ret += order_info(WHITE);
    ret += order_info(RED);
    ret += order_info(BLACK);
    ret += order_info(INITIATE);

    tmp = query_renegades();
    index = -1;
    size = sizeof(tmp);
    if (size)
        ret += "Renegades:\n";

    while (++index < size)
    {
        ret += sprintf("%11s - Color: %s\n", 
            capitalize(tmp[index]),
            query_member_type(tmp[index]));
    }
    
    return ret;
}
