/*
 * review_ob.c
 *
 * Mrpr, 1993. 
 *
 * To be used in conjunction with /cmd/wiz_cmd_normal review commands.
 */

inherit "/std/object.c";

#include <macros.h>
#include <filepath.h>
#include <std.h>

#define CALLED_FROM	"/d/Wiz/mrpr/obj/review"
#define BASE_PATH	"/d/Debug/debugwiz/reviews"
#define MORE_OBJ	"/std/board/board_more"
#define ED_OBJ		"/d/Debug/debugwiz/review_ed"
#define PO		previous_object()
#define TO		this_object()
#define RW_READ		0
#define RW_WRITE	1

nomask static string check_path(string euid, string path, int rw);
nomask static int valid_rw_dir(string euid, string path, int what);
nomask static int valid_rw_file(string euid, string dir, string file, int what);

create_object()
{
    if (IS_CLONE)
    {
	remove_object();
	return;
    }

    seteuid(getuid());
}

nomask public string
cd_dir(string p1, string p2)
{
    string path;

    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return "#Illegal call.\n";

    path = check_path(geteuid(PO), p1 + "/" + p2, RW_READ);

    /*
     * Check that it is a directory.
     */
    if (path[0] != '#' && file_size(BASE_PATH + path) != -2)
	return "#Not a directory.\n";
    else
	return path;
}

nomask public string
cp_files(string base, string f1, string f2, string text, int state)
{
    string f1n, f2n, f1p, f2p, *parts;

    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return "#Illegal call.\n";

    /*
     * Check from path.
     */
    parts = explode(f1, "/");
    if (sizeof(parts) > 1)
    {
	f1n = parts[sizeof(parts) - 1];
	f1p = implode(parts[0..(sizeof(parts) - 2)], "/");
    }
    else
    {
	f1n = parts[0];
	f1p = "";
    }
    
    if (strlen(f1) && f1[0] == '@')
    {
	f1p = FTPATH(".", f1p[1..strlen(f1p)]);
	if (!strlen(f1p))
	    return "#Illegal path: " + f1p + ".\n";
    }
    else
    {
	f1p = check_path(geteuid(PO), base + "/" + f1p, RW_READ);
	if (f1p[0] == '#')
	    return f1p;
	f1p = BASE_PATH + f1p;
    }
    if (f1p[strlen(f1p) - 1] != '/')
	f1p += "/";
    
    if (file_size(f1p + f1n) < 0)
	return "#Illegal file: " + f1 + ".\n";
    
    if (state == 0) /* Initial state */
    {
	if (!SECURITY->valid_read(f1p + f1n, geteuid(TO), "cp_files"))
	    return "#Read: " + f1p + f1n;

 	text = read_file(f1p + f1n);
    }

    /*
     * Check to path.
     */
    parts = explode(f2, "/");
    if (sizeof(parts) > 1)
    {
	f2n = parts[sizeof(parts) - 1];
	f2p = implode(parts[0..(sizeof(parts) - 2)], "/");
    }
    else
    {
	f2n = parts[0];
	f2p = "";
    }
    
    if (strlen(f2) && f2[0] == '@')
    {
	f2p = FTPATH(".", f2p[1..strlen(f2p)]);
	if (!strlen(f2p))
	    return "#Illegal path: " + f2p + ".\n";
    }
    else
    {
	f2p = check_path(geteuid(PO), base + "/" + f2p, RW_WRITE);
	if (f2p[0] == '#')
	    return f2p;
	f2p = BASE_PATH + f2p;
	if (file_size(f2p + "/" + f2n) == -2)
	{
	    f2p = check_path(geteuid(PO), f2p + "/" + f2n, RW_WRITE);
	    if (f2p[0] == '#')
		return f2p;
	    f2n = f1n;
	}
    }
    if (f2p[strlen(f2p) - 1] != '/')
	f2p += "/";
    
    if (!SECURITY->valid_write(f2p + f2n, geteuid(TO), "cp_files"))
	return "#Write:" + f2p + f2n + ":" + text;

    write_file(f2p + f2n, text);
    return "";
}

nomask public string
ed_file(string path, string file)
{
    object ed_ob;
    string *parts, fname, fpath;

    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return "#Illegal call.\n";

    /*
     * Check the given path.
     */
    parts = explode(file, "/");
    fname = parts[sizeof(parts) - 1];
    if (strlen(fname) < strlen(file))
	fpath = file[0..(strlen(file) - strlen(fname) - 1)];
    else
	fpath = "";
    path = check_path(geteuid(PO), path + "/" + fpath, RW_WRITE);

    if (path[0] == '#')
	return path;

    if (path[strlen(path) - 1] != '/')
	path += "/";

    if (file_size(BASE_PATH + path + fname) == -2)
	return "#That is a directory.\n";

    ed_ob = clone_object(ED_OBJ);
    export_uid(ed_ob);
    return ed_ob->ed_file(BASE_PATH + path + fname);
}

nomask public string *
ls_dir(string path)
{
    string *rval, *org;
    int i;

    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return ({ "#Illegal call.\n" });

    /*
     * Check the given path.
     */
    path = check_path(geteuid(PO), path, RW_READ);
    if (path[0] == '#')
	return ({ path });
    if (file_size(BASE_PATH + path) != -2)
	return ({ "#Not a directory.\n" });

    path = BASE_PATH + path;
    if (path[strlen(path) - 1] != '/')
	path += "/";

    org = get_dir(path + "*");
    rval = ({});
    for (i = 0 ; i < sizeof(org) ; i++)
    {
	if (org[i] == "." ||
	    org[i] == "..")
	    continue;

	if (!valid_rw_file(geteuid(PO), path, org[i], 0))
	    continue;

	if (file_size(path + org[i]) == -2)
	    rval += ({ org[i] + "/" });
	else
	    rval += ({ org[i] });
    }

    return rval;
}

nomask public mixed
more_file(string path, string file)
{
    object more_ob;

    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return ({ "#Illegal call.\n", 0 });

    /*
     * Check the given path.
     */
    path = check_path(geteuid(PO), path + "/" + file, RW_READ);

    if (path[0] == '#')
	return ({ path, 0 });

    /*
     * Try to read a directory.
     */
    if (file_size(BASE_PATH + path) == -2)
	return ({ "#You can't read a directory.\n", 0});

    write("--------> Review file: " +  path + "\n");

    more_ob = clone_object(MORE_OBJ);
    export_uid(more_ob);
    more_ob->more(BASE_PATH + path, 1);
    return ({ "", more_ob });
}

nomask public string
rm_file(string path, string file)
{
    if (function_exists("get_soul_id", PO) != CALLED_FROM)
	return "#Illegal call.\n";

    /*
     * Check the given path.
     */
    path = check_path(geteuid(PO), path + "/" + file, RW_WRITE);

    if (path[0] == '#')
	return path;

    if (file_size(path) == -2)
	return "#You can not rm directories.\n";

    if (rm(BASE_PATH + path))
	return path;
    else
	return "#Could not remove file.\n";
}

nomask static string
check_path(string euid, string path, int rw)
{
    string *parts, file;
    int type, res;

    /*
     * Check for //-occurances and deal with it.
     */
    parts = explode(path, "//");
    if (sizeof(parts))
	path = "/" + parts[sizeof(parts) - 1];
    parts = explode(path, "/");
    if (sizeof(parts))
	file = parts[sizeof(parts) - 1];
    else
	file = "";
    
    /*
     * Do an 'ordinary' path buildup.
     */
    path = FTPATH(path, ".");
    if (!strlen(path))
	return("#Illegal path syntax.\n");

    if ((type = file_size(BASE_PATH + path)) == -1)
	return "#Illegal path, that file/directory does not exist.\n";

    /*
     * Check priviliges now.
     */
    if (type == -2)
	res = valid_rw_dir(euid, path, rw);
    else
	res = valid_rw_file(euid, path, file, rw);
    
    if (res)
	return path;
    else
	return "#Permission denied.\n";
}

nomask static int
valid_rw_file(string euid, string dir, string file, int what)
{
    string *fname, *dmem;

    /*
     * Reviewers and arches has global read and write.
     */
    if (SECURITY->query_global_read()[euid] ||
	WIZ_TYPE(SECURITY->query_wiz_level(euid)) >= WIZ_ARCH)
	return 1;

    /*
     * No write privvs as yet for any other.
     */
    if (what == RW_WRITE)
	return 0;

    /*
     * You can not read files directed at other members in your domain.
     */
    fname = explode(file, ".");
    dmem = SECURITY->query_domain_members(SECURITY->query_wiz_dom(euid));
    if (member_array(fname[0], dmem) >= 0 && fname[0] != euid)
	return 0;

    return 1;
}

nomask static int
valid_rw_dir(string euid, string path, int what)
{
    string dom, *ppath;

    /*
     * Reviewers and arches has global read and write.
     */
    if (SECURITY->query_global_read()[euid] ||
	WIZ_TYPE(SECURITY->query_wiz_level(euid)) >= WIZ_ARCH)
	return 1;

    /*
     * No one else can write.
     */
    if (what == RW_WRITE)
	return 0;

    ppath = explode(path, "/");

    /*
     * Everone can read in /.
     */
    if (!sizeof(ppath))
	return 1;

    /*
     * You can read in your domain.
     */
    dom = SECURITY->query_wiz_dom(euid);

    if (dom == ppath[0])
	return 1;

    return 0;
}
