// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/matrix.h>
#include <khiva_jni/matrix.h>
#include <khiva_jni/internal/util.h>
#include <iostream>

using namespace khiva::bindings::jni;

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNDiscords(JNIEnv *env, jobject, jlong ref_profile,
                                                                    jlong ref_index, jlong m, jlong n,
                                                                    jboolean self_join) {
    try {
        const jint l = 5;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_profile = (af_array)ref_profile;
        af::array var_profile;

        auto arr_index = (af_array)ref_index;
        af::array var_index;

        check_and_retain_arrays(arr_profile, arr_index, var_profile, var_index);

        jlong raw_pointer_discord_distances = 0;
        auto af_p_discord_distances = (af_array)raw_pointer_discord_distances;

        jlong raw_pointer_discord_indices = 0;
        auto af_p_discord_indices = (af_array)raw_pointer_discord_indices;

        jlong raw_pointer_subsequence_indices = 0;
        auto af_p_subsequence_indices = (af_array)raw_pointer_subsequence_indices;

        af::array discords;
        af::array discords_indices;
        af::array subsequence_indices;

        khiva::matrix::findBestNDiscords(var_profile, var_index, static_cast<long>(m), static_cast<long>(n), discords,
                                         discords_indices, subsequence_indices, static_cast<bool>(self_join));

        af_retain_array(&af_p_discord_distances, discords.get());
        af_retain_array(&af_p_discord_indices, discords_indices.get());
        af_retain_array(&af_p_subsequence_indices, subsequence_indices.get());

        tmp[0] = (jlong)arr_profile;
        tmp[1] = (jlong)arr_index;
        tmp[2] = (jlong)af_p_discord_distances;
        tmp[3] = (jlong)af_p_discord_indices;
        tmp[4] = (jlong)af_p_subsequence_indices;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNDiscords. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNMotifs(JNIEnv *env, jobject, jlong ref_profile,
                                                                  jlong ref_index, jlong m, jlong n,
                                                                  jboolean self_join) {
    try {
        const jint l = 5;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_profile = (af_array)ref_profile;
        af::array var_profile;

        auto arr_index = (af_array)ref_index;
        af::array var_index;

        check_and_retain_arrays(arr_profile, arr_index, var_profile, var_index);

        jlong raw_pointer_motif_distances = 0;
        auto af_p_motif_distances = (af_array)raw_pointer_motif_distances;

        jlong raw_pointer_motif_indices = 0;
        auto af_p_motif_indices = (af_array)raw_pointer_motif_indices;

        jlong raw_pointer_subsequence_indices = 0;
        auto af_p_subsequence_indices = (af_array)raw_pointer_subsequence_indices;

        af::array motifs;
        af::array motif_indices;
        af::array subsequence_indices;

        khiva::matrix::findBestNMotifs(var_profile, var_index, static_cast<long>(m), static_cast<long>(n), motifs,
                                       motif_indices, subsequence_indices, static_cast<bool>(self_join));

        af_retain_array(&af_p_motif_distances, motifs.get());
        af_retain_array(&af_p_motif_indices, motif_indices.get());
        af_retain_array(&af_p_subsequence_indices, subsequence_indices.get());

        tmp[0] = (jlong)arr_profile;
        tmp[1] = (jlong)arr_index;
        tmp[2] = (jlong)af_p_motif_distances;
        tmp[3] = (jlong)af_p_motif_indices;
        tmp[4] = (jlong)af_p_subsequence_indices;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNMotifs. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNOccurrences(JNIEnv *env, jobject, jlong ref_query,
                                                                       jlong ref_ts, jlong n) {
    try {
        const jint l = 4;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_q = (af_array)ref_query;
        af::array var_q;

        auto arr_ts = (af_array)ref_ts;
        af::array var_ts;

        check_and_retain_arrays(arr_q, arr_ts, var_q, var_ts);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        jlong raw_pointer_index = 0;
        auto af_p_index = (af_array)raw_pointer_index;

        af::array distance;
        af::array index;
        long num_occurrences = static_cast<long>(n);

        khiva::matrix::findBestNOccurrences(var_q, var_ts, num_occurrences, distance, index);

        af_retain_array(&af_p_distance, distance.get());
        af_retain_array(&af_p_index, index.get());

        tmp[0] = (jlong)arr_q;
        tmp[1] = (jlong)arr_ts;
        tmp[2] = (jlong)af_p_distance;
        tmp[3] = (jlong)af_p_index;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNOccurrences. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_mass(JNIEnv *env, jobject, jlong ref_query, jlong ref_ts) {
    try {
        const jint l = 3;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_q = (af_array)ref_query;
        af::array var_q;

        auto arr_ts = (af_array)ref_ts;
        af::array var_ts;

        check_and_retain_arrays(arr_q, arr_ts, var_q, var_ts);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        af::array distance;

        khiva::matrix::mass(var_q, var_ts, distance);

        af_retain_array(&af_p_distance, distance.get());

        tmp[0] = (jlong)arr_q;
        tmp[1] = (jlong)arr_ts;
        tmp[2] = (jlong)af_p_distance;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_mass. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stomp(JNIEnv *env, jobject, jlong ref_a, jlong ref_b, jlong m) {
    try {
        const jint l = 4;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a;

        auto arr_b = (af_array)ref_b;
        af::array var_b;

        check_and_retain_arrays(arr_a, arr_b, var_a, var_b);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        jlong raw_pointer_index = 0;
        auto af_p_index = (af_array)raw_pointer_index;

        af::array distance;
        af::array index;
        long subsequence = static_cast<long>(m);

        khiva::matrix::stomp(var_a, var_b, subsequence, distance, index);

        af_retain_array(&af_p_distance, distance.get());
        af_retain_array(&af_p_index, index.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)arr_b;
        tmp[2] = (jlong)af_p_distance;
        tmp[3] = (jlong)af_p_index;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_stomp. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stompSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        const jint l = 3;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a = af::array(arr_a);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        jlong raw_pointer_index = 0;
        auto af_p_index = (af_array)raw_pointer_index;

        af_retain_array(&arr_a, var_a.get());

        af::array distance;
        af::array index;
        long subsequence = static_cast<long>(m);

        khiva::matrix::stomp(var_a, subsequence, distance, index);

        af_retain_array(&af_p_distance, distance.get());
        af_retain_array(&af_p_index, index.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)af_p_distance;
        tmp[2] = (jlong)af_p_index;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_stompSelfJoin. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfile(JNIEnv *env, jobject, jlong ref_a, jlong ref_b,
                                                                jlong m) {
    try {
        const jint l = 4;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a;

        auto arr_b = (af_array)ref_b;
        af::array var_b;

        check_and_retain_arrays(arr_a, arr_b, var_a, var_b);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        jlong raw_pointer_index = 0;
        auto af_p_index = (af_array)raw_pointer_index;

        af::array distance;
        af::array index;
        long subsequence = static_cast<long>(m);

        khiva::matrix::matrixProfile(var_a, var_b, subsequence, distance, index);

        af_retain_array(&af_p_distance, distance.get());
        af_retain_array(&af_p_index, index.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)arr_b;
        tmp[2] = (jlong)af_p_distance;
        tmp[3] = (jlong)af_p_index;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_Matrixprofile. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        const jint l = 3;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a = af::array(arr_a);

        jlong raw_pointer_distance = 0;
        auto af_p_distance = (af_array)raw_pointer_distance;

        jlong raw_pointer_index = 0;
        auto af_p_index = (af_array)raw_pointer_index;

        af_retain_array(&arr_a, var_a.get());

        af::array distance;
        af::array index;
        long subsequence = static_cast<long>(m);

        khiva::matrix::matrixProfile(var_a, subsequence, distance, index);

        af_retain_array(&af_p_distance, distance.get());
        af_retain_array(&af_p_index, index.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)af_p_distance;
        tmp[2] = (jlong)af_p_index;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_MatrixprofileSelfJoin. Unknown reason");
    }
    return nullptr;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileLR(JNIEnv *env, jobject, jlong ref_a,
                                                                            jlong m) {
    try {
        const jint l = 5;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a = af::array(arr_a);

        af_retain_array(&arr_a, var_a.get());

        jlong raw_pointer_pleft = 0;
        auto af_p_pleft = (af_array)raw_pointer_pleft;
        jlong raw_pointer_ileft = 0;
        auto af_p_ileft = (af_array)raw_pointer_ileft;

        jlong raw_pointer_pright = 0;
        auto af_p_pright = (af_array)raw_pointer_pright;
        jlong raw_pointer_iright = 0;
        auto af_p_iright = (af_array)raw_pointer_iright;

        af::array pleft, ileft, pright, iright;
        long subsequence = static_cast<long>(m);

        khiva::matrix::matrixProfileLR(var_a, subsequence, pleft, ileft, pright, iright);

        af_retain_array(&af_p_pleft, pleft.get());
        af_retain_array(&af_p_ileft, ileft.get());
        af_retain_array(&af_p_pright, pright.get());
        af_retain_array(&af_p_iright, iright.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)af_p_pleft;
        tmp[2] = (jlong)af_p_ileft;
        tmp[3] = (jlong)af_p_pright;
        tmp[4] = (jlong)af_p_iright;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_matrixProfileLR. Unknown reason");
    }
    return nullptr;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_getChains(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr_a = (af_array)ref_a;
        af::array var_a = af::array(arr_a);

        jlong raw_pointer_chains = 0;
        auto af_p_chains = (af_array)raw_pointer_chains;

        af_retain_array(&arr_a, var_a.get());

        af::array chains;
        long subsequence = static_cast<long>(m);

        khiva::matrix::getChains(var_a, subsequence, chains);

        af_retain_array(&af_p_chains, chains.get());

        tmp[0] = (jlong)arr_a;
        tmp[1] = (jlong)af_p_chains;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return nullptr;
}
