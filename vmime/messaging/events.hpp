//
// VMime library (http://vmime.sourceforge.net)
// Copyright (C) 2002-2005 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef VMIME_MESSAGING_EVENTS_HPP_INCLUDED
#define VMIME_MESSAGING_EVENTS_HPP_INCLUDED


#include <vector>

#include "vmime/utility/path.hpp"


namespace vmime {
namespace messaging {

class folder;

namespace events {


/** Event about the message count in a folder.
  */

class messageCountEvent
{
public:

	enum Types
	{
		TYPE_ADDED,     /**< New messages have been added. */
		TYPE_REMOVED    /**< Messages have been expunged (renumbering). */
	};


	messageCountEvent(folder* folder, const Types type, const std::vector <int>& nums);

	/** Return the folder in which messages have been added/removed.
	  *
	  * @return folder in which message count changed
	  */
	const folder* getFolder() const;

	/** Return the event type.
	  *
	  * @return event type (see messageCountEvent::Types)
	  */
	const Types getType() const;

	/** Return the numbers of the messages that have been added/removed.
	  *
	  * @return a list of message numbers
	  */
	const std::vector <int>& getNumbers() const;

	/** Dispatch the event to the specified listener.
	  *
	  * @param listener listener to notify
	  */
	void dispatch(class messageCountListener* listener) const;

private:

	folder* m_folder;
	const Types m_type;
	std::vector <int> m_nums;
};


/** Listener for events about the message count in a folder.
  */

class messageCountListener
{
protected:

	virtual ~messageCountListener() { }

public:

	virtual void messagesAdded(const messageCountEvent& event) = 0;
	virtual void messagesRemoved(const messageCountEvent& event) = 0;
};


/** Event occuring on a message.
  */

class messageChangedEvent
{
public:

	enum Types
	{
		TYPE_FLAGS    // flags changed
	};


	messageChangedEvent(folder* folder, const Types type, const std::vector <int>& nums);

	/** Return the folder in which messages have changed.
	  *
	  * @return folder in which message count changed
	  */
	const folder* getFolder() const;

	/** Return the event type.
	  *
	  * @return event type (see messageChangedEvent::Types)
	  */
	const Types getType() const;

	/** Return the numbers of the messages that have changed.
	  *
	  * @return a list of message numbers
	  */
	const std::vector <int>& getNumbers() const;

	/** Dispatch the event to the specified listener.
	  *
	  * @param listener listener to notify
	  */
	void dispatch(class messageChangedListener* listener) const;

private:

	folder* m_folder;
	const Types m_type;
	std::vector <int> m_nums;
};


/** Listener for events occuring on a message.
  */

class messageChangedListener
{
protected:

	virtual ~messageChangedListener() { }

public:

	virtual void messageChanged(const messageChangedEvent& event) = 0;
};


/** Event occuring on a folder.
  */

class folderEvent
{
public:

	enum Types
	{
		TYPE_CREATED,   /**< A folder was created. */
		TYPE_DELETED,   /**< A folder was deleted. */
		TYPE_RENAMED    /**< A folder was renamed. */
	};


	folderEvent(folder* folder, const Types type, const utility::path& oldPath, const utility::path& newPath);

	/** Return the folder on which the event occured.
	  *
	  * @return folder on which the event occured
	  */
	const folder* getFolder() const;

	/** Return the event type.
	  *
	  * @return event type (see folderEvent::Types)
	  */
	const Types getType() const;

	/** Dispatch the event to the specified listener.
	  *
	  * @param listener listener to notify
	  */
	void dispatch(class folderListener* listener) const;

private:

	folder* m_folder;
	const Types m_type;
	const utility::path m_oldPath;
	const utility::path m_newPath;
};


/** Listener for events occuring on a folder.
  */

class folderListener
{
protected:

	virtual ~folderListener() { }

public:

	virtual void folderCreated(const folderEvent& event) = 0;
	virtual void folderRenamed(const folderEvent& event) = 0;
	virtual void folderDeleted(const folderEvent& event) = 0;
};


} // events
} // messaging
} // vmime


#endif // VMIME_MESSAGING_EVENTS_HPP_INCLUDED