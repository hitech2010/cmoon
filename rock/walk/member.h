#ifndef __MEMBER_H__
#define __MEMBER_H__
#include "mheads.h"

__BEGIN_DECLS

void member_refresh_info(int uin);
void member_set_unameck(CGI *cgi);
void member_remember_login(CGI *cgi, mdb_conn *conn, int uin);

int  member_release_uin(HDF *hdf, mdb_conn *conn);
int  member_confirm_uin(HDF *hdf, mdb_conn *conn);
int  member_regist_user(HDF *hdf, mdb_conn *conn);
int  member_alloc_user(HDF *hdf, mdb_conn *conn);
int  member_check_login(HDF *hdf, mdb_conn *conn);
void member_after_login(CGI *cgi, mdb_conn *conn);

int  member_get_info(mdb_conn *conn, int uin, member_t **member);

bool member_has_login(mdb_conn *conn, int uin, char *ckusn);
bool member_in_group(member_t *mb, int gid);
bool member_is_owner(member_t *mb, int uid);
bool member_is_root(int uin);

int  member_login_data_get(CGI *cgi, HASH *dbh);
int  member_logout_data_get(CGI *cgi, HASH *dbh);
int  member_regist_data_get(CGI *cgi, HASH *dbh);

__END_DECLS
#endif	/* __MEMBER_H__ */