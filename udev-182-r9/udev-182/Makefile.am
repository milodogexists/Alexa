# Copyright (C) 2008-2012 Kay Sievers <kay.sievers@vrfy.org>
# Copyright (C) 2009 Diego Elio 'Flameeyes' Pettenò <flameeyes@gmail.com>

SUBDIRS = .

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

AM_MAKEFLAGS = --no-print-directory

LIBUDEV_CURRENT=13
LIBUDEV_REVISION=1
LIBUDEV_AGE=13

LIBGUDEV_CURRENT=1
LIBGUDEV_REVISION=1
LIBGUDEV_AGE=1

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I$(top_srcdir)/src \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DPKGLIBEXECDIR=\""$(libexecdir)/udev"\"

AM_CFLAGS = \
	${my_CFLAGS} \
	-fvisibility=hidden \
	-ffunction-sections \
	-fdata-sections

AM_LDFLAGS = \
	-Wl,--gc-sections \
	-Wl,--as-needed

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-debug \
	--enable-rule_generator \
	--enable-floppy \
	--with-selinux \
	--enable-gtk-doc \
	--with-systemdsystemunitdir=$$dc_install_base/$(systemdsystemunitdir)

BUILT_SOURCES =
EXTRA_DIST =
CLEANFILES =
INSTALL_EXEC_HOOKS =
INSTALL_DATA_HOOKS =
UNINSTALL_EXEC_HOOKS =
DISTCHECK_HOOKS =
DISTCLEAN_LOCAL_HOOKS =

udevhomedir = $(libexecdir)/udev
udevhome_SCRIPTS =
dist_udevhome_SCRIPTS =
dist_udevhome_DATA =
dist_man_MANS =

SED_PROCESS = \
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(SED) \
	-e 's,@VERSION\@,$(VERSION),g' \
	-e 's,@prefix\@,$(prefix),g' \
	-e 's,@rootprefix\@,$(rootprefix),g' \
	-e 's,@exec_prefix\@,$(exec_prefix),g' \
	-e 's,@libdir\@,$(libdir),g' \
	-e 's,@includedir\@,$(includedir),g' \
	-e 's,@bindir\@,$(bindir),g' \
	-e 's,@pkglibexecdir\@,$(libexecdir)/udev,g' \
	< $< > $@ || rm $@

%.pc: %.pc.in Makefile
	$(SED_PROCESS)

%.rules: %.rules.in Makefile
	$(SED_PROCESS)

%.service: %.service.in Makefile
	$(SED_PROCESS)

%.sh: %.sh.in Makefile
	$(SED_PROCESS)
	$(AM_V_GEN)chmod +x $@

%.pl: %.pl.in Makefile
	$(SED_PROCESS)
	$(AM_V_GEN)chmod +x $@

# ------------------------------------------------------------------------------
SUBDIRS += src/docs

include_HEADERS = src/libudev.h
lib_LTLIBRARIES = libudev.la
noinst_LTLIBRARIES = libudev-private.la

libudev_la_SOURCES =\
	src/libudev-private.h \
	src/libudev.c \
	src/libudev-list.c \
	src/libudev-util.c \
	src/libudev-device.c \
	src/libudev-enumerate.c \
	src/libudev-monitor.c \
	src/libudev-queue.c

libudev_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	-version-info $(LIBUDEV_CURRENT):$(LIBUDEV_REVISION):$(LIBUDEV_AGE)

libudev_private_la_SOURCES =\
	$(libudev_la_SOURCES) \
	src/libudev-util-private.c \
	src/libudev-device-private.c \
	src/libudev-queue-private.c

if WITH_SELINUX
libudev_private_la_SOURCES += src/libudev-selinux-private.c
libudev_private_la_LIBADD = $(SELINUX_LIBS)
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libudev.pc
EXTRA_DIST += src/libudev.pc.in
CLEANFILES += src/libudev.pc

EXTRA_DIST += src/COPYING
# move lib from $(libdir) to $(rootlib_execdir) and update devel link, if needed
libudev-install-move-hook:
	if test "$(libdir)" != "$(rootlib_execdir)"; then \
		mkdir -p $(DESTDIR)$(rootlib_execdir) && \
		so_img_name=$$(readlink $(DESTDIR)$(libdir)/libudev.so) && \
		so_img_rel_target_prefix=$$(echo $(libdir) | sed 's,\(^/\|\)[^/][^/]*,..,g') && \
		ln -sf $$so_img_rel_target_prefix$(rootlib_execdir)/$$so_img_name $(DESTDIR)$(libdir)/libudev.so && \
		mv $(DESTDIR)$(libdir)/libudev.so.* $(DESTDIR)$(rootlib_execdir); \
	fi

libudev-uninstall-move-hook:
	rm -f $(DESTDIR)$(rootlib_execdir)/libudev.so*

INSTALL_EXEC_HOOKS += libudev-install-move-hook
UNINSTALL_EXEC_HOOKS += libudev-uninstall-move-hook

# ------------------------------------------------------------------------------
udev-confdirs:
	-mkdir -p $(DESTDIR)$(sysconfdir)/udev/rules.d
	-mkdir -p $(DESTDIR)$(libexecdir)/udev/devices

INSTALL_DATA_HOOKS += udev-confdirs

udevrulesdir = $(libexecdir)/udev/rules.d
dist_udevrules_DATA = \
	rules/42-usb-hid-pm.rules \
	rules/50-udev-default.rules \
	rules/60-persistent-storage-tape.rules \
	rules/60-persistent-serial.rules \
	rules/60-persistent-input.rules \
	rules/60-persistent-alsa.rules \
	rules/60-persistent-storage.rules \
	rules/75-net-description.rules \
	rules/75-tty-description.rules \
	rules/78-sound-card.rules \
	rules/80-drivers.rules \
	rules/95-udev-late.rules

udevconfdir = $(sysconfdir)/udev
dist_udevconf_DATA = src/udev.conf

sharepkgconfigdir = $(datadir)/pkgconfig
sharepkgconfig_DATA = src/udev.pc
EXTRA_DIST += src/udev.pc.in
CLEANFILES += src/udev.pc

if WITH_SYSTEMD
dist_systemdsystemunit_DATA = \
	src/udev-control.socket \
	src/udev-kernel.socket

systemdsystemunit_DATA = \
	src/udev.service \
	src/udev-trigger.service \
	src/udev-settle.service

EXTRA_DIST += \
	src/udev.service.in \
	src/udev-trigger.service.in \
	src/udev-settle.service.in

CLEANFILES += \
	src/udev.service \
	src/udev-trigger.service \
	src/udev-settle.service

systemd-install-hook:
	mkdir -p $(DESTDIR)$(systemdsystemunitdir)/sockets.target.wants
	ln -sf ../udev-control.socket $(DESTDIR)$(systemdsystemunitdir)/sockets.target.wants/udev-control.socket
	ln -sf ../udev-kernel.socket $(DESTDIR)$(systemdsystemunitdir)/sockets.target.wants/udev-kernel.socket
	mkdir -p $(DESTDIR)$(systemdsystemunitdir)/basic.target.wants
	ln -sf ../udev.service $(DESTDIR)$(systemdsystemunitdir)/basic.target.wants/udev.service
	ln -sf ../udev-trigger.service $(DESTDIR)$(systemdsystemunitdir)/basic.target.wants/udev-trigger.service

INSTALL_DATA_HOOKS += systemd-install-hook
endif

bin_PROGRAMS = \
	udevadm

pkglibexec_PROGRAMS = \
	udevd

udev_common_sources = \
	src/udev.h \
	src/udev-event.c \
	src/udev-watch.c \
	src/udev-node.c \
	src/udev-rules.c \
	src/udev-ctrl.c \
	src/udev-builtin.c \
	src/udev-builtin-blkid.c \
	src/udev-builtin-firmware.c \
	src/udev-builtin-hwdb.c \
	src/udev-builtin-input_id.c \
	src/udev-builtin-kmod.c \
	src/udev-builtin-path_id.c \
	src/udev-builtin-usb_id.c

udev_common_CFLAGS = \
	$(BLKID_CFLAGS) \
	$(KMOD_CFLAGS)

udev_common_LDADD = \
	libudev-private.la \
	$(BLKID_LIBS) \
	$(KMOD_LIBS)

udev_common_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-DFIRMWARE_PATH="$(FIRMWARE_PATH)" \
	-DUSB_DATABASE=\"$(USB_DATABASE)\" -DPCI_DATABASE=\"$(PCI_DATABASE)\"

udevd_SOURCES = \
	$(udev_common_sources) \
	src/udevd.c \
	src/sd-daemon.h \
	src/sd-daemon.c
udevd_CFLAGS = $(udev_common_CFLAGS)
udevd_LDADD = $(udev_common_LDADD)
udevd_CPPFLAGS = $(udev_common_CPPFLAGS)

udevadm_SOURCES = \
	$(udev_common_sources) \
	src/udevadm.c \
	src/udevadm-info.c \
	src/udevadm-control.c \
	src/udevadm-monitor.c \
	src/udevadm-settle.c \
	src/udevadm-trigger.c \
	src/udevadm-test.c \
	src/udevadm-test-builtin.c
udevadm_CFLAGS = $(udev_common_CFLAGS)
udevadm_LDADD = $(udev_common_LDADD)
udevadm_CPPFLAGS = $(udev_common_CPPFLAGS)

# ------------------------------------------------------------------------------
if ENABLE_MANPAGES
dist_man_MANS += \
	src/udev.7 \
	src/udevadm.8 \
	src/udevd.8
endif

EXTRA_DIST += \
	src/udev.xml \
	src/udevadm.xml \
	src/udevd.xml

if HAVE_XSLTPROC
dist_noinst_DATA = \
	src/udev.html \
	src/udevadm.html \
	src/udevd.html

src/%.7 src/%.8 : src/%.xml
	$(AM_V_GEN)$(XSLTPROC) -o $@ -nonet http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<

src/%.html : src/%.xml
	$(AM_V_GEN)$(XSLTPROC) -o $@ -nonet http://docbook.sourceforge.net/release/xsl/current/xhtml-1_1/docbook.xsl $<
endif

# ------------------------------------------------------------------------------
TESTS = \
	test/udev-test.pl \
	test/rules-test.sh

check_PROGRAMS = \
	test-libudev \
	test-udev

test_libudev_SOURCES = src/test-libudev.c
test_libudev_LDADD = libudev.la

test_udev_SOURCES = \
	$(udev_common_sources) \
	src/test-udev.c
test_udev_CFLAGS = $(udev_common_CFLAGS)
test_udev_LDADD = $(udev_common_LDADD)
test_udev_CPPFLAGS = $(udev_common_CPPFLAGS)
test_udev_DEPENDENCIES = test/sys

# packed sysfs test tree
test/sys:
	$(AM_V_GEN)mkdir -p test && tar -C test/ -xJf $(top_srcdir)/test/sys.tar.xz

test-sys-distclean:
	-rm -rf test/sys
DISTCLEAN_LOCAL_HOOKS += test-sys-distclean

EXTRA_DIST += test/sys.tar.xz

# ------------------------------------------------------------------------------
ata_id_SOURCES = src/ata_id/ata_id.c
ata_id_LDADD = libudev-private.la
pkglibexec_PROGRAMS += ata_id

# ------------------------------------------------------------------------------
cdrom_id_SOURCES = src/cdrom_id/cdrom_id.c
cdrom_id_LDADD = libudev-private.la
pkglibexec_PROGRAMS += cdrom_id
dist_udevrules_DATA += src/cdrom_id/60-cdrom_id.rules

# ------------------------------------------------------------------------------
collect_SOURCES = src/collect/collect.c
collect_LDADD = libudev-private.la
pkglibexec_PROGRAMS += collect

# ------------------------------------------------------------------------------
scsi_id_SOURCES =\
	src/scsi_id/scsi_id.c \
	src/scsi_id/scsi_serial.c \
	src/scsi_id/scsi.h \
	src/scsi_id/scsi_id.h
scsi_id_LDADD = libudev-private.la
pkglibexec_PROGRAMS += scsi_id
dist_man_MANS += src/scsi_id/scsi_id.8
EXTRA_DIST += src/scsi_id/README

# ------------------------------------------------------------------------------
v4l_id_SOURCES = src/v4l_id/v4l_id.c
v4l_id_LDADD = libudev-private.la
pkglibexec_PROGRAMS += v4l_id
dist_udevrules_DATA += src/v4l_id/60-persistent-v4l.rules

# ------------------------------------------------------------------------------
accelerometer_SOURCES = src/accelerometer/accelerometer.c
accelerometer_LDADD = libudev-private.la -lm
pkglibexec_PROGRAMS += accelerometer
dist_udevrules_DATA += src/accelerometer/61-accelerometer.rules

# ------------------------------------------------------------------------------
if ENABLE_GUDEV
SUBDIRS += src/gudev/docs

libgudev_includedir=$(includedir)/gudev-1.0/gudev
libgudev_include_HEADERS = \
	src/gudev/gudev.h \
	src/gudev/gudevenums.h \
	src/gudev/gudevenumtypes.h \
	src/gudev/gudevtypes.h \
	src/gudev/gudevclient.h \
	src/gudev/gudevdevice.h \
	src/gudev/gudevenumerator.h

lib_LTLIBRARIES += libgudev-1.0.la

pkgconfig_DATA += src/gudev/gudev-1.0.pc
EXTRA_DIST += src/gudev/gudev-1.0.pc.in
CLEANFILES += src/gudev/gudev-1.0.pc

libgudev_1_0_la_SOURCES = \
	src/gudev/gudevenums.h \
	src/gudev/gudevenumtypes.h \
	src/gudev/gudevenumtypes.h\
	src/gudev/gudevtypes.h \
	src/gudev/gudevclient.h \
	src/gudev/gudevclient.c \
	src/gudev/gudevdevice.h \
	src/gudev/gudevdevice.c \
	src/gudev/gudevenumerator.h \
	src/gudev/gudevenumerator.c \
	src/gudev/gudevprivate.h

nodist_libgudev_1_0_la_SOURCES = \
	src/gudev/gudevmarshal.h \
	src/gudev/gudevmarshal.c \
	src/gudev/gudevenumtypes.h \
	src/gudev/gudevenumtypes.c
BUILT_SOURCES += $(nodist_libgudev_1_0_la_SOURCES)

libgudev_1_0_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	-I$(top_builddir)/src\
	-I$(top_srcdir)/src\
	-I$(top_builddir)/src/gudev \
	-I$(top_srcdir)/src/gudev \
	-D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT \
	-D_GUDEV_COMPILATION \
	-DG_LOG_DOMAIN=\"GUdev\"

libgudev_1_0_la_CFLAGS = \
	-fvisibility=default \
	$(GLIB_CFLAGS)

libgudev_1_0_la_LIBADD = libudev.la $(GLIB_LIBS)

libgudev_1_0_la_LDFLAGS = \
	-version-info $(LIBGUDEV_CURRENT):$(LIBGUDEV_REVISION):$(LIBGUDEV_AGE) \
	-export-dynamic -no-undefined \
	-export-symbols-regex '^g_udev_.*'

EXTRA_DIST += \
	src/gudev/COPYING \
	src/gudev/gudevmarshal.list \
	src/gudev/gudevenumtypes.h.template \
	src/gudev/gudevenumtypes.c.template \
	src/gudev/gjs-example.js \
	src/gudev/seed-example-enum.js \
	src/gudev/seed-example.js

src/gudev/gudevmarshal.h: src/gudev/gudevmarshal.list
	$(AM_V_GEN)glib-genmarshal $< --prefix=g_udev_marshal --header > $@

src/gudev/gudevmarshal.c: src/gudev/gudevmarshal.list
	$(AM_V_GEN)echo "#include \"gudevmarshal.h\"" > $@ && \
	glib-genmarshal $< --prefix=g_udev_marshal --body >> $@

src/gudev/gudevenumtypes.h: src/gudev/gudevenumtypes.h.template src/gudev/gudevenums.h
	$(AM_V_GEN)glib-mkenums --template $^ > \
	    $@.tmp && mv $@.tmp $@

src/gudev/gudevenumtypes.c: src/gudev/gudevenumtypes.c.template src/gudev/gudevenums.h
	$(AM_V_GEN)glib-mkenums --template $^ > \
	    $@.tmp && mv $@.tmp $@

if ENABLE_INTROSPECTION
src/gudev/GUdev-1.0.gir: libgudev-1.0.la $(G_IR_SCANNER)
	$(AM_V_GEN)$(G_IR_SCANNER) -v \
		--warn-all \
		--namespace GUdev \
		--nsversion=1.0 \
		--include=GObject-2.0 \
		--library=gudev-1.0 \
		--library-path=$(top_builddir)/src \
		--library-path=$(top_builddir)/src/gudev \
		--output $@ \
		--pkg=glib-2.0 \
		--pkg=gobject-2.0 \
		--pkg-export=gudev-1.0 \
		--c-include=gudev/gudev.h \
		-I$(top_srcdir)/src/\
		-I$(top_builddir)/src/\
		-D_GUDEV_COMPILATION \
		-D_GUDEV_WORK_AROUND_DEV_T_BUG \
		$(top_srcdir)/src/gudev/gudev.h \
		$(top_srcdir)/src/gudev/gudevtypes.h \
		$(top_srcdir)/src/gudev/gudevenums.h \
		$(or $(wildcard $(top_builddir)/src/gudev/gudevenumtypes.h),$(top_srcdir)/src/gudev/gudevenumtypes.h) \
		$(top_srcdir)/src/gudev/gudevclient.h \
		$(top_srcdir)/src/gudev/gudevdevice.h \
		$(top_srcdir)/src/gudev/gudevenumerator.h \
		$(top_srcdir)/src/gudev/gudevclient.c \
		$(top_srcdir)/src/gudev/gudevdevice.c \
		$(top_srcdir)/src/gudev/gudevenumerator.c

src/gudev/GUdev-1.0.typelib: src/gudev/GUdev-1.0.gir $(G_IR_COMPILER)
	$(AM_V_GEN)g-ir-compiler $< -o $@

girdir = $(GIRDIR)
gir_DATA = src/gudev/GUdev-1.0.gir

typelibsdir = $(GIRTYPELIBDIR)
typelibs_DATA = src/gudev/GUdev-1.0.typelib

CLEANFILES += $(gir_DATA) $(typelibs_DATA)
endif # ENABLE_INTROSPECTION

# move lib from $(libdir) to $(rootlib_execdir) and update devel link, if needed
libgudev-install-move-hook:
	if test "$(libdir)" != "$(rootlib_execdir)"; then \
		mkdir -p $(DESTDIR)$(rootlib_execdir) && \
		so_img_name=$$(readlink $(DESTDIR)$(libdir)/libgudev-1.0.so) && \
		so_img_rel_target_prefix=$$(echo $(libdir) | sed 's,\(^/\|\)[^/][^/]*,..,g') && \
		ln -sf $$so_img_rel_target_prefix$(rootlib_execdir)/$$so_img_name $(DESTDIR)$(libdir)/libgudev-1.0.so && \
		mv $(DESTDIR)$(libdir)/libgudev-1.0.so.* $(DESTDIR)$(rootlib_execdir); \
	fi

libgudev-uninstall-move-hook:
	rm -f $(DESTDIR)$(rootlib_execdir)/libgudev-1.0.so*

INSTALL_EXEC_HOOKS += libgudev-install-move-hook
UNINSTALL_EXEC_HOOKS += libgudev-uninstall-move-hook
endif

# ------------------------------------------------------------------------------
if ENABLE_KEYMAP
keymap_SOURCES = src/keymap/keymap.c
keymap_CPPFLAGS = $(AM_CPPFLAGS) -I src/keymap
nodist_keymap_SOURCES = \
	src/keymap/keys-from-name.h \
	src/keymap/keys-to-name.h
BUILT_SOURCES += $(nodist_keymap_SOURCES)

pkglibexec_PROGRAMS += keymap
dist_doc_DATA = src/keymap/README.keymap.txt

dist_udevrules_DATA += \
	src/keymap/95-keymap.rules \
	src/keymap/95-keyboard-force-release.rules

dist_udevhome_SCRIPTS += src/keymap/findkeyboards
udevhome_SCRIPTS += src/keymap/keyboard-force-release.sh

EXTRA_DIST += \
	src/keymap/check-keymaps.sh \
	src/keymap/keyboard-force-release.sh.in

CLEANFILES += \
	src/keymap/keys.txt \
	src/keymap/keys-from-name.gperf \
	src/keymap/keyboard-force-release.sh

udevkeymapdir = $(libexecdir)/udev/keymaps
dist_udevkeymap_DATA = \
	src/keymap/keymaps/acer \
	src/keymap/keymaps/acer-aspire_5720 \
	src/keymap/keymaps/acer-aspire_8930 \
	src/keymap/keymaps/acer-aspire_5920g \
	src/keymap/keymaps/acer-aspire_6920 \
	src/keymap/keymaps/acer-travelmate_c300 \
	src/keymap/keymaps/asus \
	src/keymap/keymaps/compaq-e_evo \
	src/keymap/keymaps/dell \
	src/keymap/keymaps/dell-latitude-xt2 \
	src/keymap/keymaps/everex-xt5000 \
	src/keymap/keymaps/fujitsu-amilo_li_2732 \
	src/keymap/keymaps/fujitsu-amilo_pa_2548 \
	src/keymap/keymaps/fujitsu-amilo_pro_edition_v3505 \
	src/keymap/keymaps/fujitsu-amilo_pro_v3205 \
	src/keymap/keymaps/fujitsu-amilo_si_1520 \
	src/keymap/keymaps/fujitsu-esprimo_mobile_v5 \
	src/keymap/keymaps/fujitsu-esprimo_mobile_v6 \
	src/keymap/keymaps/genius-slimstar-320 \
	src/keymap/keymaps/hewlett-packard \
	src/keymap/keymaps/hewlett-packard-2510p_2530p \
	src/keymap/keymaps/hewlett-packard-compaq_elitebook \
	src/keymap/keymaps/hewlett-packard-pavilion \
	src/keymap/keymaps/hewlett-packard-presario-2100 \
	src/keymap/keymaps/hewlett-packard-tablet \
	src/keymap/keymaps/hewlett-packard-tx2 \
	src/keymap/keymaps/ibm-thinkpad-usb-keyboard-trackpoint \
	src/keymap/keymaps/inventec-symphony_6.0_7.0 \
	src/keymap/keymaps/lenovo-3000 \
	src/keymap/keymaps/lenovo-ideapad \
	src/keymap/keymaps/lenovo-thinkpad-usb-keyboard-trackpoint \
	src/keymap/keymaps/lenovo-thinkpad_x6_tablet \
	src/keymap/keymaps/lenovo-thinkpad_x200_tablet \
	src/keymap/keymaps/lg-x110 \
	src/keymap/keymaps/logitech-wave \
	src/keymap/keymaps/logitech-wave-cordless \
	src/keymap/keymaps/logitech-wave-pro-cordless \
	src/keymap/keymaps/maxdata-pro_7000 \
	src/keymap/keymaps/medion-fid2060 \
	src/keymap/keymaps/medionnb-a555 \
	src/keymap/keymaps/micro-star \
	src/keymap/keymaps/module-asus-w3j \
	src/keymap/keymaps/module-ibm \
	src/keymap/keymaps/module-lenovo \
	src/keymap/keymaps/module-sony \
	src/keymap/keymaps/module-sony-old \
	src/keymap/keymaps/module-sony-vgn \
	src/keymap/keymaps/olpc-xo \
	src/keymap/keymaps/onkyo \
	src/keymap/keymaps/oqo-model2 \
	src/keymap/keymaps/samsung-other \
	src/keymap/keymaps/samsung-sq1us \
	src/keymap/keymaps/samsung-sx20s \
	src/keymap/keymaps/toshiba-satellite_a100 \
	src/keymap/keymaps/toshiba-satellite_a110 \
	src/keymap/keymaps/toshiba-satellite_m30x \
	src/keymap/keymaps/zepto-znote

udevkeymapforcereldir = $(libexecdir)/udev/keymaps/force-release
dist_udevkeymapforcerel_DATA = \
	src/keymap/force-release-maps/dell-touchpad \
	src/keymap/force-release-maps/hp-other \
	src/keymap/force-release-maps/samsung-other \
	src/keymap/force-release-maps/common-volume-keys

src/keymap/keys.txt: $(INCLUDE_PREFIX)/linux/input.h
	$(AM_V_at)mkdir -p src/keymap
	$(AM_V_GEN)$(AWK) '/^#define.*KEY_[^ ]+[ \t]+[0-9]/ { if ($$2 != "KEY_MAX") { print $$2 } }' < $< | sed 's/^KEY_COFFEE$$/KEY_SCREENLOCK/' > $@

src/keymap/keys-from-name.gperf: src/keymap/keys.txt
	$(AM_V_GEN)$(AWK) 'BEGIN{ print "struct key { const char* name; unsigned short id; };"; print "%null-strings"; print "%%";} { print $$1 ", " $$1 }' < $< > $@

src/keymap/keys-from-name.h: src/keymap/keys-from-name.gperf Makefile
	$(AM_V_GEN)$(GPERF) -L ANSI-C -t --ignore-case -N lookup_key -H hash_key_name -p -C < $< > $@

src/keymap/keys-to-name.h: src/keymap/keys.txt Makefile
	$(AM_V_GEN)$(AWK) 'BEGIN{ print "const char* const key_names[KEY_CNT] = { "} { print "[" $$1 "] = \"" $$1 "\"," } END{print "};"}' < $< > $@

keymaps-distcheck-hook: src/keymap/keys.txt
	$(top_srcdir)/src/keymap/check-keymaps.sh $(top_srcdir) $^
DISTCHECK_HOOKS += keymaps-distcheck-hook
endif

if ENABLE_MTD_PROBE
# ------------------------------------------------------------------------------
mtd_probe_SOURCES =  \
	src/mtd_probe/mtd_probe.c \
	src/mtd_probe/mtd_probe.h \
	src/mtd_probe/probe_smartmedia.c
mtd_probe_CPPFLAGS = $(AM_CPPFLAGS)
dist_udevrules_DATA += src/mtd_probe/75-probe_mtd.rules
pkglibexec_PROGRAMS += mtd_probe
endif

# ------------------------------------------------------------------------------
if ENABLE_RULE_GENERATOR
dist_udevhome_SCRIPTS += \
	src/rule_generator/write_cd_rules \
	src/rule_generator/write_net_rules

dist_udevhome_DATA += \
	src/rule_generator/rule_generator.functions

dist_udevrules_DATA += \
	src/rule_generator/75-cd-aliases-generator.rules \
	src/rule_generator/75-persistent-net-generator.rules
endif

# ------------------------------------------------------------------------------
if ENABLE_FLOPPY
create_floppy_devices_SOURCES = src/floppy/create_floppy_devices.c
create_floppy_devices_LDADD = libudev-private.la
pkglibexec_PROGRAMS += create_floppy_devices
dist_udevrules_DATA += src/floppy/60-floppy.rules
endif

# ------------------------------------------------------------------------------
clean-local:
	rm -rf udev-test-install

distclean-local:
	rm -rf autom4te.cache

EXTRA_DIST += \
	$(TESTS) \
	test/rule-syntax-check.py

CLEANFILES += \
	$(BUILT_SOURCES)

install-exec-hook: $(INSTALL_EXEC_HOOKS)

install-data-hook: $(INSTALL_DATA_HOOKS)

uninstall-hook: $(UNINSTALL_EXEC_HOOKS)

distcheck-hook: $(DISTCHECK_HOOKS)

distclean-local: $(DISTCLEAN_LOCAL_HOOKS)

# ------------------------------------------------------------------------------
PREVIOUS_VERSION = `expr $(VERSION) - 1`
changelog:
	@ head -1 ChangeLog | grep -q "to v$(PREVIOUS_VERSION)"
	@ mv ChangeLog ChangeLog.tmp
	@ echo "Summary of changes from v$(PREVIOUS_VERSION) to v$(VERSION)" >> ChangeLog
	@ echo "============================================" >> ChangeLog
	@ echo >> ChangeLog
	@ git log --pretty=short $(PREVIOUS_VERSION)..HEAD | git shortlog  >> ChangeLog
	@ echo >> ChangeLog
	@ cat ChangeLog
	@ cat ChangeLog.tmp >> ChangeLog
	@ rm ChangeLog.tmp

test-install:
	rm -rf $(PWD)/udev-test-install/
	make DESTDIR=$(PWD)/udev-test-install install
	tree $(PWD)/udev-test-install/

git-release:
	head -1 ChangeLog | grep -q "to v$(VERSION)"
	head -1 NEWS | grep -q "udev $(VERSION)"
	git commit -a -m "release $(VERSION)"
	git tag -m "udev $(VERSION)" -s $(VERSION)
	git gc --prune=0

git-sync:
	git push
	git push --tags

tar-sync:
	rm -f udev-$(VERSION).tar.sign
	xz -d -c udev-$(VERSION).tar.xz | gpg --armor --detach-sign --output udev-$(VERSION).tar.sign
	kup put udev-$(VERSION).tar.xz  udev-$(VERSION).tar.sign /pub/linux/utils/kernel/hotplug/

doc-sync:
	for i in src/*.html; do rm -f $$i.sign; gpg --armor --detach-sign --output=$$i.sign $$i; done
	for i in src/*.html; do echo $$i; kup put $$i $$i.sign /pub/linux/utils/kernel/hotplug/udev/; done
	for i in src/docs/html/*.{html,css,png}; do rm -f $$i.sign; gpg --armor --detach-sign --output=$$i.sign $$i; done
	for i in src/docs/html/*.{html,css,png}; do echo $$i; kup put $$i $$i.sign /pub/linux/utils/kernel/hotplug/libudev/; done
	for i in src/gudev/docs/html/*.{html,css,png}; do rm -f $$i.sign; gpg --armor --detach-sign --output=$$i.sign $$i; done
	for i in src/gudev/docs/html/*.{html,css,png}; do echo $$i; kup put $$i $$i.sign /pub/linux/utils/kernel/hotplug/gudev/; done
