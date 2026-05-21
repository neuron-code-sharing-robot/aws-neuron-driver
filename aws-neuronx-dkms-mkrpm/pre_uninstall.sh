echo -e
echo -e "Uninstall of MODULE_NAME module (version MODULE_VERSION) beginning:"
if lsmod | grep -q "^neuron "; then
    echo "Neuron module is currently loaded. Attempting to unload..."
    if ! rmmod neuron 2>/dev/null; then
        echo "ERROR: Cannot unload neuron module - it is currently in use."
        echo "Please stop all processes using the neuron module before uninstalling."
        exit 1
    fi
fi
dkms remove -m MODULE_NAME -v MODULE_VERSION --all --rpm_safe_upgrade
exit 0
