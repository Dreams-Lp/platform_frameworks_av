/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DRM_ERROR_EVENT_H__
#define __DRM_ERROR_EVENT_H__

#include "drm_framework_common.h"

namespace android {

class String8;

/**
 * This is an entity class which would be passed to caller in
 * DrmManagerClient::OnErrorListener::onError(const DrmErrorEvent&).
 */
class DrmErrorEvent {
public:
    /**
     * The following constant values should be in sync with DrmErrorEvent.java
     */
    //! TYPE_RIGHTS_NOT_INSTALLED, when something went wrong installing the rights
    static const int TYPE_RIGHTS_NOT_INSTALLED = 2001;
    //! TYPE_RIGHTS_RENEWAL_NOT_ALLOWED, when the server rejects renewal of rights
    static const int TYPE_RIGHTS_RENEWAL_NOT_ALLOWED = 2002;
    //! TYPE_NOT_SUPPORTED, when answer from server can not be handled by the native agent
    static const int TYPE_NOT_SUPPORTED = 2003;
    //! TYPE_OUT_OF_MEMORY, when memory allocation fail during renewal.
    //! Can in the future perhaps be used to trigger garbage collector
    static const int TYPE_OUT_OF_MEMORY = 2004;
    //! TYPE_NO_INTERNET_CONNECTION, when the Internet connection is missing and no attempt
    //! can be made to renew rights
    static const int TYPE_NO_INTERNET_CONNECTION = 2005;
    //! TYPE_PROCESS_DRM_INFO_FAILED, when failed to process DrmInfo.
    static const int TYPE_PROCESS_DRM_INFO_FAILED = 2006;
    //! TYPE_REMOVE_ALL_RIGHTS_FAILED, when failed to remove all the rights objects
    //! associated with all DRM schemes.
    static const int TYPE_REMOVE_ALL_RIGHTS_FAILED = 2007;
    //! TYPE_ACQUIRE_DRM_INFO_FAILED, when failed to acquire DrmInfo.
    static const int TYPE_ACQUIRE_DRM_INFO_FAILED = 2008;

public:
    /**
     * Constructor for DrmErrorEvent.
     * Data in drmBuffer are copied to newly allocated buffer.
     *
     * @param[in] uniqueId Unique session identifier
     * @param[in] infoType Type of information
     * @param[in] message Message description
     * @param[in] drmBuffer Binary information
     */
    DrmErrorEvent(int uniqueId, int infoType, const String8 message);
    DrmErrorEvent(int uniqueId, int infoType, const String8 message, const DrmBuffer& drmBuffer);

    /**
     * Destructor for DrmErrorEvent
     */
    ~DrmErrorEvent();

public:
    /**
     * Iterator for key
     */
    class KeyIterator {
        friend class DrmErrorEvent;

    private:
        KeyIterator(const DrmErrorEvent* drmErrorEvent)
                : mDrmErrorEvent(const_cast <DrmErrorEvent*> (drmErrorEvent)), mIndex(0) {}

    public:
        KeyIterator(const KeyIterator& keyIterator);
        KeyIterator& operator=(const KeyIterator& keyIterator);
        virtual ~KeyIterator() {}

    public:
        bool hasNext();
        const String8& next();

    private:
        DrmErrorEvent* mDrmErrorEvent;
        unsigned int mIndex;
    };

    /**
     * Iterator
     */
    class Iterator {
        friend class DrmErrorEvent;

    private:
        Iterator(const DrmErrorEvent* drmErrorEvent)
                : mDrmErrorEvent(const_cast <DrmErrorEvent*> (drmErrorEvent)), mIndex(0) {}

    public:
        Iterator(const Iterator& iterator);
        Iterator& operator=(const Iterator& iterator);
        virtual ~Iterator() {}

    public:
        bool hasNext();
        const String8& next();

    private:
        DrmErrorEvent* mDrmErrorEvent;
        unsigned int mIndex;
    };

public:
    /**
     * Returns the Unique Id associated with this instance
     *
     * @return Unique Id
     */
    int getUniqueId() const;

    /**
     * Returns the Type of information associated with this object
     *
     * @return Type of information
     */
    int getType() const;

    /**
     * Returns the message description associated with this object
     *
     * @return Message description
     */
    const String8 getMessage() const;

    /**
     * Returns the number of attributes contained in this instance
     *
     * @return Number of attributes
     */
    int getCount() const;

    /**
     * Adds optional information as <key, value> pair to this instance
     *
     * @param[in] key Key to add
     * @param[in] value Value to add
     * @return Returns the error code
     */
    status_t put(const String8& key, String8& value);

    /**
     * Retrieves the value of given key
     *
     * @param key Key whose value to be retrieved
     * @return The value
     */
    const String8 get(const String8& key) const;

    /**
     * Returns KeyIterator object to walk through the keys associated with this instance
     *
     * @return KeyIterator object
     */
    KeyIterator keyIterator() const;

    /**
     * Returns Iterator object to walk through the values associated with this instance
     *
     * @return Iterator object
     */
    Iterator iterator() const;

    /**
     * Returns the Binary information associated with this instance
     *
     * @return Binary information
     */
    const DrmBuffer& getData() const;

    /**
     * Sets the Binary information associated with this instance.
     * Data in drmBuffer are copied to newly allocated buffer.
     *
     * @param[in] drmBuffer Binary information associated with this instance
     */
    void setData(const DrmBuffer& drmBuffer);

private:
    int mUniqueId;
    int mInfoType;
    const String8 mMessage;
    KeyedVector<String8, String8> mAttributes;
    DrmBuffer mDrmBuffer;
};

};

#endif /* __DRM_ERROR_EVENT_H__ */

