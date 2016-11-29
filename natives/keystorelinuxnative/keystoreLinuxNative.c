/**
 * Copyright (c) 2016 Julien HENRY.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 */
#include <jni.h>
#include "keystoreLinuxNative.h"
#include <libsecret/secret.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

const SecretSchema *
equinox_get_schema (void)
{
    static const SecretSchema the_schema = {
        "org.eclipse.equinox", SECRET_SCHEMA_NONE,
        {
            {  "NULL", 0 },
        }
    };
    return &the_schema;
}

#define EQUINOX_SCHEMA  equinox_get_schema ()

JNIEXPORT jstring JNICALL Java_org_eclipse_equinox_internal_security_linux_LinuxPasswordProvider_getMasterPassword(JNIEnv *env, jobject this) {
  GError *error = NULL;
  jstring result;
  
	gchar *password = secret_password_lookup_sync (EQUINOX_SCHEMA, NULL, &error,
	                                               NULL);
	
	if (error != NULL) {
	    (*env)->ExceptionClear(env);
			char buffer [60];
			sprintf(buffer, "%s.  Result: %d", error->message, error->code);
			(*env)->ThrowNew(env, (* env)->FindClass(env, "java/lang/SecurityException"), buffer);
	    g_error_free (error);
	} else if (password == NULL) {
	    (*env)->ExceptionClear(env);
			(*env)->ThrowNew(env, (* env)->FindClass(env, "java/lang/SecurityException"), "Unable to find password");
	} else {
	    result = (*env)->NewStringUTF(env, password);
			free(password);
	    return result;
	}
}

JNIEXPORT void JNICALL Java_org_eclipse_equinox_internal_security_linux_LinuxPasswordProvider_saveMasterPassword(JNIEnv *env, jobject this, jstring password) {
	GError *error = NULL;
	
	const char *passwordUTF = (*env)->GetStringUTFChars(env, password, NULL);
	secret_password_store_sync (EQUINOX_SCHEMA, SECRET_COLLECTION_DEFAULT,
	                            "Equinox master password", passwordUTF, NULL, &error,
	                            NULL);
	
	// free the UTF strings
	(*env)->ReleaseStringUTFChars( env, password, passwordUTF );

	if (error != NULL) {
    (*env)->ExceptionClear(env);
		char buffer [60];
		sprintf(buffer, "%s.  Result: %d", error->message, error->code);
		(*env)->ThrowNew(env, (* env)->FindClass(env, "java/lang/SecurityException"), buffer);
		g_error_free (error);
	}
}

