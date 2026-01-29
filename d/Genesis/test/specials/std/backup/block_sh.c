inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define TP            this_player()
#define TO            this_object()
#define QSW           query_shadow_who()
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()

static object * Blockers = ({ });

static int Move_alarmid;

static string How="";

static mixed To_dest;

static int Dont_follow;

static int No_glance;

static int Seconds_attempted=0;

static object Last_blocker;


public mixed query_blocked()
{
    return Blockers - ({ });
}


static nomask int
fixnorm(int offence, int defence)
{
   if (offence + defence == 0)
       return 0;

   return ((100 * offence) / (offence + defence));
}

public int query_strength(object blocker)
{
    int offense=blocker->query_stat(SS_STR)+blocker->query_stat(SS_DEX)
                +blocker->query_stat(SS_CON);

    int defense=TO->query_stat(SS_STR)+TO->query_stat(SS_DEX)
                +TO->query_stat(SS_CON);
    
    int multiplier=1;
    
    if (environment(QSW)->query_prop(ROOM_I_INSIDE))
    {
        multiplier=2;
    }
    //0 to 33 seconds, double for indoors
    return fixnorm(offense,defense)*multiplier/3;
    
}

public object check_blocker()
{
    int block_strength=0;
    
    foreach(object blocker : query_blocked())
    {
        if (!objectp(blocker))
            continue;
        //Not in the same room?
        if (environment(blocker)!=environment(QSW))
            continue;

        //Wrong exit?
        if (blocker->query_blocker_exit()!=How)
            continue;

        //Is the blocker trying to move?
        if (blocker->query_blocker_moving())
            continue;

        //Can't be fighting somebody different and blocking 
        if (blocker->query_attack()!=QSW &&
            QSW->query_attack()!=blocker)
            continue;            
        
        //Is the blocker blinded?
        if (!CAN_SEE_IN_ROOM(blocker))
            continue;
            
        //Can the blocker sneak by?
        if (!QSW->check_seen(blocker))
            continue;
            
        block_strength+=query_strength(blocker);
        if (block_strength>Seconds_attempted)
        {
            if (objectp(Last_blocker) && blocker!=Last_blocker)
            {
                TO->catch_msg("You have gotten through the block of "+
                    QTNAME(Last_blocker) + ", but still have "+
                    QTNAME(blocker) + " in your way.\n");
            }
            Last_blocker=blocker;
            return blocker;
        }
    }

    return 0;
}


public varargs int 
attempt_move()
{
    if (How=="")
    {
        return 7;
    }

    Seconds_attempted++;

    object blocker=check_blocker();
    
    if (blocker)
    {
        return 7;
    }
    
    int result=QSW->move_living(How, To_dest, Dont_follow, No_glance);
    
    if (!result)
    {
        if (objectp(Last_blocker))
        {
            TO->catch_msg("You break through the block and leave.\n");
        }
        remove_alarm(Move_alarmid);
        set_alarm(0.1,0.0,remove_shadow);
    }

    return result;    

}


public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{

    if (how!=How)
    {
        How=how;
        To_dest=to_dest;
        Dont_follow=dont_follow;
        No_glance=no_glance;
        Seconds_attempted=0;
        Last_blocker=0;
        if (Move_alarmid)
        {
            remove_alarm(Move_alarmid);
        }
    }

    int result=attempt_move();
    
    if (result)
    {
        object blocker=check_blocker();
        if (objectp(blocker))
        {
            TO->catch_msg("You try to pass " + QTNAME(blocker) + " but "+
            PRO(blocker) + " is still in your way. You keep trying but "+
            "this will take more time.\n");
            tell_room(environment(TO),QCTNAME(TO)+" tries to leave but "+
            "is blocked by " +QTNAME(blocker) + ".\n", ({ TO }) );
            blocker->catch_msg(QCTNAME(TO)+" tries to leave but is " +
            "successfully blocked by you.\n");
            if (!Move_alarmid)
            {
                Move_alarmid=set_alarm(1.0,1.0,attempt_move);
            }
        }
    }
    return result;
}



public void add_blocker(object blocker)
{
    if (member_array(blocker,Blockers)<0)
    {
        Blockers+=({ blocker });
    }
}

public void remove_blocker(object blocker)
{
    int old_size=sizeof(Blockers);
    
    Blockers-=({ blocker });
    
    if (sizeof(Blockers)!=old_size)
    {
        attempt_move();
        if (!sizeof(Blockers))
        {
            remove_shadow();
        }
    }
}
