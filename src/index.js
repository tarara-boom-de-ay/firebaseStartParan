// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyAYpdumbNhMsTEO7n7D7enGV1PBytInsRs",
  authDomain: "fir-startparan.firebaseapp.com",
  projectId: "fir-startparan",
  storageBucket: "fir-startparan.appspot.com",
  messagingSenderId: "794090027369",
  appId: "1:794090027369:web:62b4c706efe0112214e5f8",
  measurementId: "G-YW0PJXV6XR"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
console.log(app)