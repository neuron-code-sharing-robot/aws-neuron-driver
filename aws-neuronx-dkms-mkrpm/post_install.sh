for POSTINST in /usr/lib/dkms/common.postinst /usr/share/MODULE_NAME/postinst; do
    if [ -f $POSTINST ]; then
        $POSTINST MODULE_NAME MODULE_VERSION /usr/share/MODULE_NAME
        exit $?
    fi
    echo "WARNING: $POSTINST does not exist."
done
echo -e "ERROR: DKMS version is too old and MODULE_NAME was not"
echo -e "built with legacy DKMS support."
echo -e "You must either rebuild MODULE_NAME with legacy postinst"
echo -e "support or upgrade DKMS to a more current version."
exit 1
