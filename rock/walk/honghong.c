#include "mheads.h"
#include "lheads.h"
#include "omember.h"
#include "ofile.h"
#include "ogroup.h"
#include "oaccount.h"
#include "ocsc.h"

int admin_account_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	return account_get_accounts(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_account_data_add(CGI *cgi, HASH *dbh, session_t *ses)
{
	return account_add_partner(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_file_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	int ret;
	ret = file_get_files(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
	file_translate_mode(cgi->hdf);
	return ret;
}

int admin_file_data_mod(CGI *cgi, HASH *dbh, session_t *ses)
{
	return file_modify(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_file_data_add(CGI *cgi, HASH *dbh, session_t *ses)
{
	return file_add(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_file_data_del(CGI *cgi, HASH *dbh, session_t *ses)
{
	return file_delete(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}


int admin_group_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	return group_get_groups(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_group_data_mod(CGI *cgi, HASH *dbh, session_t *ses)
{
	return group_add_member(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_group_data_add(CGI *cgi, HASH *dbh, session_t *ses)
{
	return group_add_member(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}

int admin_group_data_del(CGI *cgi, HASH *dbh, session_t *ses)
{
	return group_del_member(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}


int member_login_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	int ret;
	
	mdb_conn *conn = (mdb_conn*)hash_lookup(dbh, "Sys");
	ret = member_check_login(cgi->hdf, conn);
	if (ret == RET_RBTOP_OK) {
		member_after_login(cgi, conn);
	}
	return ret;
}

int member_logout_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	int uin = hdf_get_int_value(cgi->hdf, PRE_COOKIE".uin", 0);
	mtc_info("%d logout", uin);
	member_refresh_info(uin);

	return RET_RBTOP_OK;
}

int member_regist_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	int ret;
	
	mdb_conn *conn = (mdb_conn*)hash_lookup(dbh, "Sys");
	ret = member_regist_user(cgi->hdf, conn);
	if (ret == RET_RBTOP_OK) {
		member_after_login(cgi, conn);
	}
	return ret;
}


int service_action_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	return file_get_action(cgi->hdf,
						   (mdb_conn*)hash_lookup(dbh, "Sys"), ses);
}


int static_csc_data_get(HDF *hdf, HASH *dbh)
{
	return file_get_nav_by_uri((mdb_conn*)hash_lookup(dbh, "Sys"),
							   "/csc", PRE_OUTPUT, hdf);
}


int csc_data_get(CGI *cgi, HASH *dbh, session_t *ses)
{
	int ret;
	
	if (ses->file != NULL)
		lutil_fill_layout_by_file((mdb_conn*)hash_lookup(dbh, "Sys"),
								  ses->file, cgi->hdf);
	hdf_set_value(cgi->hdf, PRE_OUTPUT".navtitle", "菜色");
	file_get_nav_by_uri((mdb_conn*)hash_lookup(dbh, "Sys"),
						"/csc", PRE_OUTPUT, cgi->hdf);

	ret = file_check_user_power(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Sys"),
								ses, ses->file, LMT_APPEND);
	if (ret == RET_RBTOP_OK) {
		hdf_set_value(cgi->hdf, PRE_OUTPUT".appendable", "1");
	}
	return RET_RBTOP_OK;
	//return csc_get_data(cgi->hdf, (mdb_conn*)hash_lookup(dbh, "Csc"));

}

int csc_data_add(CGI *cgi, HASH *dbh, session_t *ses)
{
	char *tp = hdf_get_value(cgi->hdf, PRE_QUERY".tp", NULL);

	if (tp != NULL && !strcmp(tp, "imageadd")) {
		return csc_add_image(cgi, (mdb_conn*)hash_lookup(dbh, "Csc"), ses);
	}

	return csc_add_item(cgi, (mdb_conn*)hash_lookup(dbh, "Csc"), ses);
}