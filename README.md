# org.eclipse.equinox.security.linux
Fragment to have Eclipse secure storage use native Linux password storage

# References
https://specifications.freedesktop.org/secret-service/
https://bugs.eclipse.org/bugs/show_bug.cgi?id=234509
https://wiki.gnome.org/Projects/Libsecret
https://github.com/eclipse/rt.equinox.bundles/tree/master/bundles/org.eclipse.equinox.security.macosx

Unfortunately, libsecret is still not the "standard" since it seems KDE has not completed the implementation:
https://www.reddit.com/r/kde/comments/5avpj3/ksecretservice_news/
https://github.com/KDE/ksecrets
https://community.kde.org/KDE_Utils/ksecretsservice

At least on my Fedora box where I try to use KDE only, the master password was not visible in KWalletManager but instead in Seahorse.

https://m7i.org/tips/chromium-keyring/
