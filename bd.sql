-- Create table for users
CREATE TABLE users (
    user_id NUMBER PRIMARY KEY,
    username VARCHAR2(100) UNIQUE,
    first_name VARCHAR2(100),
    last_name VARCHAR2(100)
);

-- Create table for reports
CREATE TABLE reports (
    report_id NUMBER PRIMARY KEY,
    report_title VARCHAR2(255),
    report_description VARCHAR2(1000),
    user_id NUMBER,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);
