/*
 * netcf.h: public interface for libnetcf
 *
 * Copyright (C) 2007 Red Hat Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: David Lutterkort <dlutter@redhat.com>
 */

#ifndef NETCF_H_
#define NETCF_H_

/*
 * FIXME: We need a way to distinguish between 'active' interfaces (i.e.,
 * ones that are up) and ones that are merely defined; maybe punt that to
 * clients ?
 *
 * FIXME: NM needs a way to be notified of changes to the underlying
 * network files, either we provide a way to register callbacks for an
 * interface, or we hand out a list of files that contain the configs for
 * the interface.
 *
 */

/* The main object for netcf, for internal state tracking */
struct netcf;

/* An individual interface (connection) */
struct netcf_if;

struct netcf *ncf_init(void);
void ncf_close(struct netcf *);

/* Number of known interfaces and list of them.
 * For listing we identify the interfaces by UUID, since we don't want
 * to assume that each interface has a (device) name or a hwaddr.
 *
 * Maybe we should just list them as STRUCT NETCF_IF *
 */
int
ncf_num_of_interfaces(struct netcf *);
int
ncf_list_interfaces(struct netcf *, int maxuuid, char **uuids);

/* Look up interfaces by UUID, name and hwaddr (MAC-48) */
struct netcf_if *
ncf_lookup_by_uuid_string(struct netcf *, const char *uuid);
struct netcf_if *
ncf_lookup_by_name(struct netcf *, const char *name);
/* MAC is 48 bit (6 byte) array */
struct netcf_if *
ncf_lookup_by_mac(struct netcf *, const unsigned char *mac);

/*
 * Define/start/stop/undefine interfaces
 */

/* Define a new interface */
struct netcf_if *
ncf_define(struct netcf *, const char *xml);

/* Bring the interface up */
int ncf_up(struct netcf_if *);

/* Take it down */
int ncf_down(struct netcf_if *);

/* Delete the definition */
int ncf_undefine(struct netcf_if *);

/* Produce an XML description for the interface, in the same format that
 * NCF_DEFINE expects
 */
char *ncf_xml_desc(struct netcf_if *);

/* Release any resources used by this NETCF_IF; the pointer is invalid
 * after this call
 */
int ncf_free(struct netcf_if *);

#endif


/*
 * Local variables:
 *  indent-tabs-mode: nil
 *  c-indent-level: 4
 *  c-basic-offset: 4
 *  tab-width: 4
 * End:
 */