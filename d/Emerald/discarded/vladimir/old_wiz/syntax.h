#define LINES ({ \
    "public int", \
    "e_#emote#(string arg)", \
    "{", \
    "    object *oblist;", \
    "    string *how;", \
    "    notify_fail(#fail#);", \
    "    how = parse_adverb_with_space(arg, #default#, #trail#);", \
    "    arg = how[0];", \
    "    if (strlen(arg))", \
    "        return 0;", \
    "    all#bb#(#all#);", \
    "    write(#write#);", \
    "    if (!strlen(arg))", \
    "    {", \
    "        all#bb#(#all#);", \
    "        write(#write#);", \
    "        return 1;", \
    "    }", \
    "        return 0;", \
    "", \
    "    oblist = parse_this(arg, #parse#);", \
    "    if (!sizeof(oblist))", \
    "        return 0;", \
    "    actor(#actor#);", \
    "    all2act#bb#(#all2act#);", \
    "    target#btb#(#target#);", \
    "    return 1;", \
    "}" })
 
#define OPTIONS ({ ({ 19, 0, 1, 2, 5, 8, 9, 19, 10, 11, 26, 27 }), \
    ({ 19, 0, 1, 2, 4, 19, 5, 19, 6, 7, 8, 9, 19, 10, 11, 26, 27 }), \
    ({ 19, 0, 1, 2, 3, 19, 5, 19, 12, 13, 14, 15, 16, 17, 19, 20, 21, \
       22, 19, 23, 24, 25, 26, 27 }), ({ 19, 0, 1, 2, 3, 4, 19, 5, 19, 6, \
       7, 19, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27 }), \
    ({ 19, 0, 1, 2, 3, 19, 5, 12, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 }), \
    ({ 19, 0, 1, 2, 3, 4, 19, 5, 19, 6, 7, 19, 12, 18, 19, 20, 21, 22, 19, \
       23, 24, 25, 26, 27 }) })
