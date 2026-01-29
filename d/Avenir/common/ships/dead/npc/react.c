#pragma strict_types
 
static string *react_pat;
static int c_parse,
          in_react;
static mixed b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
static mixed react_arr;
 
mixed react_check(string str, string pat, int index);
 
/*
 * Function name: catch_tell
 * Description:   This is the text that normal players gets written to
 *                their sockets.
 */
public void
catch_tell(string str)
{
    int i;
    string pattern, func;
 
    if (query_ip_number(this_object())) // Monster is possessed
    {
        write_socket(str);
        return;
    }
 
    if (in_react)
    {
        return;
    }
    for (c_parse = 0, i = sizeof(react_pat); c_parse < i; c_parse++)
    {
        if (stringp(react_pat[c_parse])) 
        {
            pattern = process_string(react_pat[c_parse], 1);
            if (react_check(str, pattern, c_parse))
                return;
        }
    }
}
 
public mixed
get_all_args()
{
    return ({ b1, b2, b3, b4, b5, b6, b7, b8, b9, b10 });
}
 
mixed
react_check(string str, string pat, int index)
{
    int pmatch, split;
    object ob;
 
    if (!stringp(pat))
        return 0;
 
    split = sizeof(explode("dummy" + pat + "dummy", "%"));
    if (split - 1 > 10)
        return 0; /* Illegal pattern */
    
    ob = environment(this_object());
 
    if (!ob)
        return;
 
    switch (split)
    {
    case 2:
        pmatch = parse_command(str, ob, pat, b1);
        break;
    case 3:
        pmatch = parse_command(str, ob, pat, b1,b2);
        break;
    case 4:
        pmatch = parse_command(str, ob, pat, b1,b2,b3);
        break;
    case 5:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4);
        break;
    case 6:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5);
        break;
    case 7:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5,b6);
        break;
    case 8:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5,b6,b7);
        break;
    case 9:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5,b6,b7,b8);
        break;
    case 10:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5,b6,b7,b8,b9);
        break;
    case 11:
        pmatch = parse_command(str, ob, pat, b1,b2,b3,b4,b5,b6,b7,b8,b9,b10);
        break;
    }
 
    if (!pmatch)
        return 0;
    call_other(this_object(), "do_reaction", index);
    return 1;
}
 
/*
 * Description: Add a new pattern to trig on
 */
public void
react_new(string pat, mixed re_list)
{
    int pos;
 
    this_object()->set_tell_active(1); /* We want all messages sent to us */
 
    if ((pos = member_array(pat, react_pat)) >= 0)
        react_arr[pos] = re_list;
 
    if (!sizeof(react_pat))
    {
        react_pat = ({});
        react_arr = ({});
     }
    react_pat += ({ pat });
    react_arr += ({ re_list });
}
 
/*
 *  Description: Delete a pattern from the ones to trig on
 */
void
react_delete(string pat)
{
    int pos;
 
    if ((pos = member_array(pat, react_pat)) >= 0)
    {
        react_pat = exclude_array(react_pat, pos, pos);
        react_arr = exclude_array(react_arr, pos, pos);
    }
}
 
public string
l_case(string arg)
{
    return lower_case(arg);
}
 
public void
re_do(mixed arg)
{
    mixed ob;
    string d1, d2;
    int i;
    seteuid(getuid());
    arg = process_string(arg, 1);
    if (!stringp(arg) || !strlen(arg))
        return;
     arg = "dummy " + arg + " dummy";
    ob = get_all_args();
    while(sscanf(arg, "%s#%d#%s", d1, i, d2) == 3)
        arg = sprintf("%s%s%s", d1, ob[i], d2);
    while(sscanf(arg, "%s#%d:%s#%s", d1, i, d2, arg) == 4)
        arg = sprintf("%s%s%s", d1, call_other(this_object(), d2, ob[i]), arg);
    sscanf(arg, "dummy %s dummy", arg);
    this_object()->command(arg);
}
 
public void
unreact()
{
    in_react = 0;
}
 
public void
do_reaction(int index)
{
    int i, j;
    mixed arr;
    in_react = 1;
    arr = react_arr[index];
    j = sizeof(arr);
    for (i = 0, j; i < j - 1; i += 2)
       set_alarm(arr[i], 0.0, "re_do", arr[i+1]);
   set_alarm(arr[sizeof(arr) - 2] + 0.1, 0.0, "unreact");
}
