/*
   intro.c

   Inherit this module if your npc has to introduce itself.
   
   Fysix@Genesis, Oct 1997
 */
#pragma strict_types
#pragma save_binary

// --- Globals ---
static float  Delay = 1.0,          // delay before introing
              Forget_delay = 600.0; // delay after which the npc forgets
static string *Introed = ({ });     // array of remembered names

/* Function name: do_introduce
 * Description:   Introduce myself to somebody
 * Arguments:     string name
 */
public void
do_introduce(string name)
{
   command("introduce me to " + name);
}

/* Function name: try_introduce
 * Description:   Try to introduce, check if the living is
 *                present first. If present call do_introduce.
 *                Called by add_introduced.
 * Arguments:     
 * Returns:       
 */
public void
try_introduce(string name)
{
   if (present(name, environment()))
      do_introduce(name);
}

/* Function name: forget
 * Description:   Forget a name, called by add_introduced via an alarm.
 * Arguments:     string name
 */
public void
forget(string name)
{
   Introed -= ({ name });
}

/* Function name: add_introduced
 * Description:   This function is called when somebody
 *                introduces himself to this living.
 * Arguments:     string name
 */
public void
add_introduced(mixed who)
{
object living;
string name;

   if (stringp(who))
      living = present(who, environment());
   else if (objectp(who))
      living = who;
   else
      return;

   if ((!living) || (member_array(name = living->query_real_name(),
      Introed) >= 0))
      return;

   Introed += ({ name });
  
   set_alarm(Delay, 0.0, &try_introduce(name));

   if (Forget_delay >= 0.0)
      set_alarm(Forget_delay, 0.0, &forget(name));
}  

/* Function name: query_introed
 * Description:   Who have introed to this living?
 * Returns:       string* array of names.
 */
public string*
query_introed()
{
   return Introed;
}

/* Function name: intro_reset
 * Description:   Forget everybody.
 */
public void
intro_reset()
{
   Introed = ({ });
}

/* Function name: set_intro_delay
 * Description:   Set the time it takes before the living
 *                introduces himself.
 * Arguments:     mixed
 */
public void
set_intro_delay(mixed i)
{
   if (intp(i))
   {
      Delay = itof(i);
      return;
   }

   if (!floatp(i))
      return;

   Delay = i;
}

/* Function name: query_intro_delay
 * Description:   How many seconds does it take before the living
 *                introduces himself.
 * Returns:       float
 */
public float 
query_intro_delay()
{
   return Delay;
}

/* Function name: set_forget_delay
 * Description:   Set the amount of seconds it takes before the living
 *                forgets a name.
 * Arguments:     mixed the amount of seconds, if negative the living
 *                does not forget.
 */
public void
set_forget_delay(mixed i)
{
   if (intp(i))
   {
      Forget_delay = itof(i);
      return;
   }

   if (!floatp(i))
      return;

   Forget_delay = i;
}

/* Function name: query_forget_delay
 * Description:   How many seconds does it take before the living
 *                forgets a name?
 * Returns:       float the time in seconds. if negative the living does
 *                not forget.
 */
public float
query_forget_delay()
{
   return Forget_delay;
}
